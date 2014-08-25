#include "GLWidget3D.h"
#include "MainWindow.h"
#include <gl/GLU.h>
#include "OBJLoader.h"

GLWidget3D::GLWidget3D(MainWindow* mainWin) : QGLWidget(QGLFormat(QGL::SampleBuffers), (QWidget*)mainWin) {
	this->mainWin = mainWin;

	camera2D.resetCamera();

	camera2D.setRotation(0, 0, 0);
	camera2D.setTranslation(0, 0, 10);
}

void GLWidget3D::mousePressEvent(QMouseEvent *event) {
	this->setFocus();

	lastPos = event->pos();

	if (event->buttons() & Qt::LeftButton) {
	}
}

void GLWidget3D::mouseReleaseEvent(QMouseEvent *event) {

	updateGL();

	return;
}

void GLWidget3D::mouseMoveEvent(QMouseEvent *event) {
	float dx = (float)(event->x() - lastPos.x());
	float dy = (float)(event->y() - lastPos.y());

	if (event->buttons() & Qt::LeftButton) {	// Rotate
		camera2D.changeXRotation(dy);
		camera2D.changeYRotation(dx);
		updateCamera();
		lastPos = event->pos();
	} else if (event->buttons() & Qt::MidButton) {
		camera2D.changeXYZTranslation(-dx, dy, 0);
		updateCamera();
		lastPos = event->pos();
	} else if (event->buttons() & Qt::RightButton) {	// Zoom
		camera2D.changeXYZTranslation(0, 0, -dy);
		updateCamera();
		lastPos = event->pos();
	}

	updateGL();
}

void GLWidget3D::initializeGL() {
	// init glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		qDebug() << "Error: " << glewGetErrorString(err);
	}

	shader.createProgram("shaders/lc_vertex_sk.glsl", "shaders/lc_fragment_sk.glsl");
	glUseProgram(shader.program);

	qglClearColor(QColor(113, 112, 117));
	//qglClearColor(QColor(0, 0, 0));

	glEnable(GL_DEPTH_TEST);

	OBJLoader::load("models/triangle.obj", vertices);
	createVAO(vertices, vao, vbo);

	updateCamera();
}

void GLWidget3D::resizeGL(int width, int height) {
	updateCamera();
}

void GLWidget3D::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_TEXTURE_2D);
	
	drawScene();		
}

/**
 * シーンを描画
 */
void GLWidget3D::drawScene() {	
	glUniform1i(glGetUniformLocation (shader.program, "mode"), 0x200|1);
	glUniform1i(glGetUniformLocation (shader.program, "tex0"), 0);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES,0,vertices.size());
}

// this method should be called after any camera transformation (perspective or modelview)
// it will update viewport, perspective, view matrix, and update the uniforms
void GLWidget3D::updateCamera(){
	// update matrices
	int height = this->height() ? this->height() : 1;
	glViewport(0, 0, (GLint)this->width(), (GLint)this->height());
	camera2D.updatePerspective(this->width(),height);
	camera2D.updateCamMatrix();

	// update uniforms
	float mvpMatrixArray[16];
	float mvMatrixArray[16];

	for(int i=0;i<16;i++){
		mvpMatrixArray[i]=camera2D.mvpMatrix.data()[i];
		mvMatrixArray[i]=camera2D.mvMatrix.data()[i];	
	}
	float normMatrixArray[9];
	for(int i=0;i<9;i++){
		normMatrixArray[i]=camera2D.normalMatrix.data()[i];
	}

	glUniformMatrix4fv(glGetUniformLocation(shader.program, "mvpMatrix"),  1, false, mvpMatrixArray);
	glUniformMatrix4fv(glGetUniformLocation(shader.program, "mvMatrix"),  1, false, mvMatrixArray);
	glUniformMatrix3fv(glGetUniformLocation(shader.program, "normalMatrix"),  1, false, normMatrixArray);

	// light poss
	QVector3D light_dir(-0.2, -0.1, -1);
	light_dir.normalize();
	glUniform3f(glGetUniformLocation(shader.program, "lightDir"),light_dir.x(),light_dir.y(),light_dir.z());
}//

void GLWidget3D::createVAO(std::vector<Vertex>& vertices, GLuint& vao, GLuint& vbo)
{
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	// Crete VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	
	// Configure the attributes in the VAO.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(9*sizeof(float)));

	// Bind back to the default state.
	glBindVertexArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void GLWidget3D::loadOBJ(const char* filename)
{
	OBJLoader::load(filename, vertices);
	createVAO(vertices, vao, vbo);
}
