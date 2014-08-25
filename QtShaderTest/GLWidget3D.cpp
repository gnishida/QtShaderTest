﻿#include "GLWidget3D.h"
#include "MainWindow.h"
#include <gl/GLU.h>
#include "OBJLoader.h"

GLWidget3D::GLWidget3D()
{
	camera2D.resetCamera();
	camera2D.setRotation(0, 0, 0);
	camera2D.setTranslation(0, 0, 10);
}

void GLWidget3D::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void GLWidget3D::mouseReleaseEvent(QMouseEvent *event)
{
	updateGL();
}

void GLWidget3D::mouseMoveEvent(QMouseEvent *event)
{
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

void GLWidget3D::initializeGL()
{
	// init glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		qDebug() << "Error: " << glewGetErrorString(err);
	}

	shader.createProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
	glUseProgram(shader.program);

	qglClearColor(QColor(113, 112, 117));

	glEnable(GL_DEPTH_TEST);

	OBJLoader::load("models/triangle.obj", vertices);
	createVAO(vertices, vao, vbo);

	updateCamera();
}

void GLWidget3D::resizeGL(int width, int height)
{
	updateCamera();
}

void GLWidget3D::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_TEXTURE_2D);
	
	drawScene();		
}

/**
 * draw the scene
 */
void GLWidget3D::drawScene()
{
	// use color mode
	glUniform1i(glGetUniformLocation (shader.program, "mode"), 1);
	//glUniform1i(glGetUniformLocation (shader.program, "tex0"), 0);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES,0,vertices.size());
}

void GLWidget3D::updateCamera()
{
	int height = this->height() ? this->height() : 1;
	glViewport(0, 0, (GLint)this->width(), (GLint)this->height());
	camera2D.updatePerspective(this->width(),height);
	camera2D.updateCamMatrix();

	// update uniforms
	float mvpMatrixArray[16];
	for(int i=0;i<16;i++){
		mvpMatrixArray[i]=camera2D.mvpMatrix.data()[i];
	}
	glUniformMatrix4fv(glGetUniformLocation(shader.program, "mvpMatrix"),  1, false, mvpMatrixArray);

	// update light position
	QVector3D light_dir(-0.2, -0.1, -1);
	light_dir.normalize();
	glUniform3f(glGetUniformLocation(shader.program, "lightDir"),light_dir.x(),light_dir.y(),light_dir.z());
}

/**
 * Create VAO according to the vertices
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
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(9*sizeof(float)));

	// unbind the vao
	glBindVertexArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void GLWidget3D::loadOBJ(const char* filename)
{
	OBJLoader::load(filename, vertices);
	createVAO(vertices, vao, vbo);
}
