#include "GLWidget3D.h"
#include "MainWindow.h"
#include <gl/GLU.h>
#include "OBJLoader.h"

GLWidget3D::GLWidget3D(MainWindow* mainWin) : QGLWidget(QGLFormat(QGL::SampleBuffers), (QWidget*)mainWin) {
	this->mainWin = mainWin;

	camera2D.resetCamera();

	spaceRadius=30000.0;
	farPlaneToSpaceRadiusFactor=5.0f;//N 5.0f

	rotationSensitivity = 0.4f;
	zoomSensitivity = 10.0f;

	controlPressed=false;
	shiftPressed=false;
	altPressed=false;
	keyMPressed=false;

	camera2D.setRotation(0, 0, 0);
	camera2D.setTranslation(0, 0, 10);
}

QSize GLWidget3D::minimumSizeHint() const {
	return QSize(200, 200);
}

QSize GLWidget3D::sizeHint() const {
	return QSize(400, 400);
}

void GLWidget3D::mousePressEvent(QMouseEvent *event) {
	if (Qt::ControlModifier == event->modifiers()) {
		controlPressed = true;
	} else {
		controlPressed = false;
	}

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
		camera2D.changeXRotation(rotationSensitivity * dy);
		camera2D.changeYRotation(rotationSensitivity * dx);
		updateCamera();
		lastPos = event->pos();
	} else if (event->buttons() & Qt::MidButton) {
		camera2D.changeXYZTranslation(-dx, dy, 0);
		updateCamera();
		lastPos = event->pos();
	} else if (event->buttons() & Qt::RightButton) {	// Zoom
		camera2D.changeXYZTranslation(0, 0, -zoomSensitivity * dy);
		updateCamera();
		lastPos = event->pos();
	}

	updateGL();
}

void GLWidget3D::initializeGL() {

	qglClearColor(QColor(113, 112, 117));
	//qglClearColor(QColor(0, 0, 0));

	//---- GLEW extensions ----
	GLenum err = glewInit();
	if (GLEW_OK != err){// Problem: glewInit failed, something is seriously wrong.
		qDebug() << "Error: " << glewGetErrorString(err);
	}
	qDebug() << "Status: Using GLEW " << glewGetString(GLEW_VERSION);
	if (glewIsSupported("GL_VERSION_4_2"))
		printf("Ready for OpenGL 4.2\n");
	else {
		printf("OpenGL 4.2 not supported\n");
		exit(1);
	}
	const GLubyte* text=
		glGetString(GL_VERSION);
	printf("VERSION: %s\n",text);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	///
	//vboRenderManager.init();
	shader.createProgram("shaders/lc_vertex_sk.glsl", "shaders/lc_fragment_sk.glsl");
	glUseProgram(shader.program);

	OBJLoader::load("models/cube.obj", vertices);
	for (int i = 0; i < vertices.size(); ++i) {
		vertices[i].color[0] = 1.0f;
		vertices[i].color[1] = 0.0f;
		vertices[i].color[2] = 0.0f;
	}
	/*
	vertices.push_back(Vertex(QVector3D(-1, -1, 1), QVector3D(1, 0, 0), QVector3D(0, 0, 1), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(1, -1, 1), QVector3D(1, 0, 0), QVector3D(0, 0, 1), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(1, 1, 1), QVector3D(1, 0, 0), QVector3D(0, 0, 1), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(-1, 1, 1), QVector3D(1, 0, 0), QVector3D(0, 0, 1), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(1, -1, 1), QVector3D(1, 0, 0), QVector3D(1, 0, 0), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(1, -1, -1), QVector3D(1, 0, 0), QVector3D(1, 0, 0), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(1, 1, -1), QVector3D(1, 0, 0), QVector3D(1, 0, 0), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(1, 1, 1), QVector3D(1, 0, 0), QVector3D(1, 0, 0), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(1, 1, 1), QVector3D(1, 0, 0), QVector3D(0, 1, 0), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(1, 1, -1), QVector3D(1, 0, 0), QVector3D(0, 1, 0), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(-1, 1, -1), QVector3D(1, 0, 0), QVector3D(0, 1, 0), QVector3D(0, 0, 0)));
	vertices.push_back(Vertex(QVector3D(-1, 1, 1), QVector3D(1, 0, 0), QVector3D(0, 1, 0), QVector3D(0, 0, 0)));
	*/
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
	
	// NOTE: camera transformation is not necessary here since the updateCamera updates the uniforms each time they are changed

	drawScene();		
}

/**
 * シーンを描画
 */
void GLWidget3D::drawScene() {
	//vboRenderManager.renderStaticGeometry("test");
	
	glUniform1i (glGetUniformLocation (shader.program, "mode"), 0x200|1);
	glUniform1i (glGetUniformLocation (shader.program, "tex0"), 0);//tex0: 0

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES,0,vertices.size());
}


void GLWidget3D::keyPressEvent( QKeyEvent *e ){
	shiftPressed=false;
	controlPressed=false;
	altPressed=false;
	keyMPressed=false;

	switch( e->key() ){
	case Qt::Key_Shift:
		shiftPressed=true;
		break;
	case Qt::Key_Control:
		controlPressed=true;
		break;
	case Qt::Key_Alt:
		altPressed=true;
		break;
	case Qt::Key_Escape:
		updateGL();
		break;
	case Qt::Key_Delete:
		break;
	case Qt::Key_R:
		break;
	case Qt::Key_Up:
		break;
	case Qt::Key_Down:
		break;
	case Qt::Key_Right:
		break;
	case Qt::Key_Left:
		break;
	case Qt::Key_W:
		break;
	case Qt::Key_S:
		break;
	case Qt::Key_D:
		break;
	case Qt::Key_A:
		break;
	case Qt::Key_Q:
		break;
	default:
		;
	}
}

void GLWidget3D::keyReleaseEvent(QKeyEvent* e) {
	if (e->isAutoRepeat()) {
		e->ignore();
		return;
	}
	switch (e->key()) {
	case Qt::Key_Shift:
		shiftPressed=false;
		break;
	case Qt::Key_Control:
		controlPressed=false;
		break;
	case Qt::Key_Alt:
		altPressed=false;
	case Qt::Key_Right:
	case Qt::Key_Left:
		break;
	default:
		;
	}
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
