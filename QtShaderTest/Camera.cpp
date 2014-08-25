#include "Camera.h"

Camera::Camera() {
	xrot = 0.0f;
	yrot = 0.0;
	zrot = 0.0f;
	pos = QVector3D(0, 0, 10);
	fovy = 60.0f;
}

/**
 * Call this function when the mouse button is pressed.
 */
void Camera::mousePress(int mouse_x, int mouse_y)
{
	mouse_pos = QVector2D(mouse_x, mouse_y);
}

/**
 * Call this function whenever the mouse moves while rotating the model.
 */
void Camera::rotate(int mouse_x, int mouse_y)
{
	xrot += mouse_y - mouse_pos.y();
	yrot += mouse_x - mouse_pos.x();
	updateMVPMatrix();

	mouse_pos = QVector2D(mouse_x, mouse_y);
}

/**
 * Call this function whenever the mouse moves while zooming.
 */
void Camera::zoom(int mouse_x, int mouse_y)
{
	pos.setZ(pos.z() + mouse_pos.y() - mouse_y);
	updateMVPMatrix();

	mouse_pos = QVector2D(mouse_x, mouse_y);
}

/**
 * Call this function whenever the mouse moves while moving the model.
 */
void Camera::move(int mouse_x, int mouse_y)
{
	pos.setX(pos.x() - (mouse_x - mouse_pos.x()) * 0.1);
	pos.setY(pos.y() + (mouse_y - mouse_pos.y()) * 0.1);
	updateMVPMatrix();

	mouse_pos = QVector2D(mouse_x, mouse_y);
}

/**
 * Update perspective projection matrix, and then, update the model view projection matrix.
 */
void Camera::updatePMatrix(int width,int height) {
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
	pMatrix = QMatrix4x4(m);

	updateMVPMatrix();
}

/**
 * Update the model view projection matrix
 */
void Camera::updateMVPMatrix() {
	// create model view matrix
	mvMatrix.setToIdentity();
	mvMatrix.translate(-pos);
	mvMatrix.rotate(xrot, 1.0, 0.0, 0.0);		
	mvMatrix.rotate(yrot, 0.0, 1.0, 0.0);
	mvMatrix.rotate(zrot, 0.0, 0.0, 1.0);

	// create model view projection matrix
	mvpMatrix = pMatrix * mvMatrix;
}
