#pragma once

#include <QVector3D>

struct Vertex {
	float position[3];
	float color[3];
	float normal[3];
	float uv[3];

	Vertex() {}

	Vertex(float x,float y,float z,float r,float g,float b,float nX,float nY,float nZ,float s,float t,float w){
		position[0]=x;
		position[1]=y;
		position[2]=z;

		color[0]=r;
		color[1]=g;
		color[2]=b;

		normal[0]=nX;
		normal[1]=nY;
		normal[2]=nZ;

		uv[0]=s;
		uv[1]=t;
		uv[2]=w;
	}

	Vertex(QVector3D pos,QVector3D c,QVector3D n,QVector3D tex){
		position[0]=pos.x();
		position[1]=pos.y();
		position[2]=pos.z();

		color[0]=c.x();
		color[1]=c.y();
		color[2]=c.z();

		normal[0]=n.x();
		normal[1]=n.y();
		normal[2]=n.z();

		uv[0]=tex.x();
		uv[1]=tex.y();
		uv[2]=tex.z();
	}
};
