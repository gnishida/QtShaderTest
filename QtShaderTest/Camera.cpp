#include "Camera.h"

Camera::Camera() {
	xrot = 0.0f;
	yrot = 0.0;
	zrot = 0.0f;
	pos = QVector3D(0, 0, 10);
	fovy = 60.0f;
}

/**
 * Update projection matrix, and then, update the model view projection matrix.
 */
void Camera::updatePerspective(int width,int height) {
	float aspect = (float)width / (float)height;
	float zfar = 30000.0f;
	float znear = 0.1f;
	float f = 1.0f / tan(fovy * 3.1415926535 / 360.0f);

	double m[16]=
	{	 f/aspect,	0,								0,									0,
				0,	f,								0,						 			0,
			    0,	0,		(zfar+znear)/(znear-zfar),		(2.0f*zfar*znear)/(znear-zfar),
			    0,	0,		    				   -1,									0

	};
	pMatrix=QMatrix4x4(m);

	updateCamMatrix();
}

/**
 * Update the model view projection matrix
 */
void Camera::updateCamMatrix() {
	// create model view matrix
	mvMatrix.setToIdentity();
	mvMatrix.translate(-pos);
	mvMatrix.rotate(xrot, 1.0, 0.0, 0.0);		
	mvMatrix.rotate(yrot, 0.0, 1.0, 0.0);
	mvMatrix.rotate(zrot, 0.0, 0.0, 1.0);

	// create model view projection matrix
	mvpMatrix = pMatrix * mvMatrix;
}

void Camera::setXRotation(float angle) {
	xrot = angle;			
}

void Camera::setYRotation(float angle) {
	yrot = angle;			
}

void Camera::setZRotation(float angle) {
	zrot = angle;			
}

void Camera::changeXRotation(float angle) {
	setXRotation(xrot+angle);
}

void Camera::changeYRotation(float angle) {
	setYRotation(yrot+angle);
}

void Camera::changeZRotation(float angle) {
	setZRotation(zrot+angle);
}

void Camera::setTranslation(float x, float y, float z) {
	pos = QVector3D(x, y, z);
}

void Camera::changeXYZTranslation(float dx, float dy, float dz) {
	pos += QVector3D(dx, dy, dz);
}
