#pragma once

#include <GL/glew.h>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include "Camera.h"
#include <QVector3D>
#include <vector>
#include "Vertex.h"
#include "Shader.h"

using namespace std;

class GLWidget3D : public QGLWidget
{
public:
	void drawScene();
	void loadOBJ(const char* filename);

protected:
	void initializeGL();

	void resizeGL(int width, int height);
	void paintGL();    

	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

private:
	Camera camera;

	Shader shaderProgram;
	GLuint vao;
	GLuint vbo;
	vector<Vertex> vertices;
};

