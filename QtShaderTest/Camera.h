#pragma once

#include <GL/glew.h>
#include <QMatrix4x4>

class Camera {
public:
	Camera();

	void updatePerspective(int width,int height);
	void updateCamMatrix();
	void setXRotation(float angle);
	void setYRotation(float angle);
	void setZRotation(float angle);
	void changeXRotation(float angle);
	void changeYRotation(float angle);
	void changeZRotation(float angle);
	void setTranslation(float x, float y, float z);
	void changeXYZTranslation(float dx, float dy, float dz);

private:
	float fovy;
	QVector3D pos;
	float xrot;
	float yrot;
	float zrot;

	QMatrix4x4 mvMatrix;
	QMatrix4x4 pMatrix;

public:
	QMatrix4x4 mvpMatrix;
};

