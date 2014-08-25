#pragma once

#include <GL/glew.h>
#include <QMatrix4x4>
#include <QVector2D>

class Camera {
public:
	Camera();

	void mousePress(int mouse_x, int mouse_y);
	void rotate(int mouse_x, int mouse_y);
	void zoom(int mouse_x, int mouse_y);
	void move(int mouse_x, int mouse_y);
	void updatePMatrix(int width,int height);

private:
	void updateMVPMatrix();

private:
	float fovy;
	QVector3D pos;
	float xrot;
	float yrot;
	float zrot;
	QVector2D mouse_pos;

	QMatrix4x4 mvMatrix;
	QMatrix4x4 pMatrix;

public:
	QMatrix4x4 mvpMatrix;
};

