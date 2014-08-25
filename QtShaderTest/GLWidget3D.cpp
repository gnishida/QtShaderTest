#include "GLWidget3D.h"
#include "MainWindow.h"
#include "OBJLoader.h"

GLWidget3D::GLWidget3D()
{
}

/**
 * This event handler is called when the mouse press events occur.
 */
void GLWidget3D::mousePressEvent(QMouseEvent *e)
{
	camera.mousePress(e->x(), e->y());
}

/**
 * This event handler is called when the mouse release events occur.
 */
void GLWidget3D::mouseReleaseEvent(QMouseEvent *e)
{
}

/**
 * This event handler is called when the mouse move events occur.
 */
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
	createVAO(vertices, vao);
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

	// use texture mode
	/*
	GLuint texture = loadTexture("textures/grass.jpg");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "mode"), 2);
	glUniform1i(glGetUniformLocation (program, "tex0"), 0);
	*/

	// bind the vao and draw it.
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

/**
 * Create VAO according to the vertices.
 */
void GLWidget3D::createVAO(std::vector<Vertex>& vertices, GLuint& vao)
{
	// create vao and bind it
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	// create VBO and tranfer the vertices data to GPU buffer
	GLuint vbo;
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
void GLWidget3D::loadOBJ(const QString& filename)
{
	OBJLoader::load(filename, vertices);
	createVAO(vertices, vao);
}

/**
 * Load an image file and create a texture object.
 */
GLuint GLWidget3D::loadTexture(const QString& filename)
{
	QImage img;
	if (!img.load(filename)) {
		printf("ERROR: loading %s\n",filename.toUtf8().data());
		return INT_MAX;
	}

	QImage GL_formatted_image;
	GL_formatted_image = QGLWidget::convertToGLFormat(img);
	if (GL_formatted_image.isNull()) {
		printf("ERROR: GL_formatted_image\n");
		return INT_MAX;
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GL_formatted_image.width(), GL_formatted_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits());
	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}
