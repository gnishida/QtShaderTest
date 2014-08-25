/*********************************************************************
This file is part of QtUrban.

    QtUrban is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    QtUrban is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QtUrban.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#pragma once

#include <GL/glew.h>
#include "Shader.h"
#include "Vertex.h"

#include <QGLWidget>
#include <QMouseEvent>
#include "Camera2D.h"

class MainWindow;

class GLWidget3D : public QGLWidget {
public:
	GLWidget3D();

	void drawScene();
	void updateCamera();
	void createVAO(std::vector<Vertex>& vertices, GLuint& vao, GLuint& vbo);
	void loadOBJ(const char* filename);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();    
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

private:
	Camera2D camera2D;
	QPoint lastPos;
	GLuint vao;
	GLuint vbo;
	Shader shader;
	std::vector<Vertex> vertices;
};

