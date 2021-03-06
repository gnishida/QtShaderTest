#pragma once

#include <glew.h>
#include "Shader.h"
#include "Vertex.h"
#include <QGLWidget>
#include <QMouseEvent>
#include "Camera.h"

class MainWindow;

class GLWidget3D : public QGLWidget {
public:
	void drawScene();
	void loadOBJ(const QString& filename);
	void createVAO(std::vector<Vertex>& vertices, GLuint& vao);
	GLuint loadTexture(const QString& filename);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();    
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

private:
	Camera camera;
	GLuint vao;
	GLuint program;
	std::vector<Vertex> vertices;
};

