#include "GLWidget3D.h"
#include "MainWindow.h"
#include "OBJLoader.h"

GLWidget3D::GLWidget3D()
{
}

void GLWidget3D::mousePressEvent(QMouseEvent *e)
{
	//lastPos = event->pos();
	camera.mousePress(e->x(), e->y());
}

void GLWidget3D::mouseReleaseEvent(QMouseEvent *e)
{
}

void GLWidget3D::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() & Qt::LeftButton) { // Rotate
		camera.rotate(e->x(), e->y());
	} else if (e->buttons() & Qt::MidButton) { // Move
		camera.move(e->x(), e->y());
	} else if (e->buttons() & Qt::RightButton) { // Zoom
		camera.zoom(e->x(), e->y());
	}

	updateGL();
}

/**
 * This function is called once before the first call to paintGL() or resizeGL().
 */
void GLWidget3D::initializeGL()
{
	// init glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		qDebug() << "Error: " << glewGetErrorString(err);
	}

	// load shaders
	Shader shader;
	program = shader.createProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
	glUseProgram(program);

	// set the clear color for the screen
	qglClearColor(QColor(113, 112, 117));

	// load a triangle model
	OBJLoader::load("models/triangle.obj", vertices);
	createVAO(vertices, vao, vbo);
}

/**
 * This function is called whenever the widget has been resized.
 */
void GLWidget3D::resizeGL(int width, int height)
{
	height = height ? height : 1;
	glViewport(0, 0, width, height);
	camera.updatePMatrix(width, height);
}

/**
 * This function is called whenever the widget needs to be painted.
 */
void GLWidget3D::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	// pass the model view projection matrix to the shader
	float mvpMatrixArray[16];
	float mvMatrixArray[16];
	for (int i = 0; i < 16; ++i) {
		mvpMatrixArray[i] = camera.mvpMatrix.data()[i];
		mvMatrixArray[i] = camera.mvMatrix.data()[i];
	}
	glUniformMatrix4fv(glGetUniformLocation(program, "mvpMatrix"),  1, false, mvpMatrixArray);
	glUniformMatrix4fv(glGetUniformLocation(program, "mvMatrix"),  1, false, mvMatrixArray);

	// pass the light direction to the shader
	QVector3D light_dir(-0.2, -0.1, -1);
	light_dir.normalize();
	glUniform3f(glGetUniformLocation(program, "lightDir"), light_dir.x(), light_dir.y(), light_dir.z());
	
	drawScene();		
}

/**
 * Draw the scene.
 */
void GLWidget3D::drawScene()
{
	// use color mode
	glUniform1i(glGetUniformLocation(program, "mode"), 1);
	//glUniform1i(glGetUniformLocation (shader.program, "tex0"), 0);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

/**
 * Create VAO according to the vertices.
 */
void GLWidget3D::createVAO(std::vector<Vertex>& vertices, GLuint& vao, GLuint& vbo)
{
	// create vao and bind it
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	// create VBO and tranfer the vertices data to GPU buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	
	// configure the attributes in the vao
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	// unbind the vao
	glBindVertexArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 * Load an OBJ file and create the corresponding VAO.
 */
void GLWidget3D::loadOBJ(const char* filename)
{
	OBJLoader::load(filename, vertices);
	createVAO(vertices, vao, vbo);
}
