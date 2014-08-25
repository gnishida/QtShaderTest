#pragma once

#include <GL/glew.h>
#include "VBOShader.h"
#include "VBOUtil.h"
#include "qmap.h"


const int mode_AdaptTerrain=0x0100;
const int mode_Lighting=0x0200;
const int mode_TexArray=0x0400;
const int mode_Tex3D=0x0800;

//0x0100 --> adapt vboRenderManager
//0x0200 --> lighting

struct RenderSt{
	uint texNum;//0 means use color
	//int gridIndex;
	GLuint vbo;
	GLuint vao;
	int numVertex;//defines if the vbo has been created
	std::vector<Vertex> vertices;

	GLenum geometryType;
	int shaderMode;

	RenderSt(uint _texNum,std::vector<Vertex> _vertices,GLenum geoT,int shModer){
		texNum=_texNum;
		vertices=_vertices;
		geometryType=geoT;
		shaderMode=shModer;
		numVertex=-1;
	}
	RenderSt(){
		numVertex=-1;
	}
};

typedef QHash<uint,RenderSt> renderGrid;

/////////////////////////////////////
// VBORenderManager

class VBORenderManager {

public:
	QMap<QString,int> geoNameToGeoNum;
	GLuint program;
	int currentIndexGeo;

	VBORenderManager();
	~VBORenderManager();

	void init();



	// textures
	QHash<QString,GLuint> nameToTexId;
	GLuint loadTexture(const QString fileName,bool mirrored=false);
	GLuint loadArrayTexture(QString texName,std::vector<QString> fileNames);

	//static
	bool addStaticGeometry(QString geoName,std::vector<Vertex>& vert,QString textureName,GLenum geometryType,int shaderMode);
	bool removeStaticGeometry(QString geoName);
	void renderStaticGeometry(QString geoName);
	bool checkIfGeoNameInUse(QString geoName);

	void renderAll(bool cleanVertex);
private:

	QHash<QString,QHash<int,renderGrid>> geoName2RenderGrids;
	QHash<QString,renderGrid> geoName2StaticRender;

	void renderVAO(RenderSt& renderSt,bool cleanVertex);
	bool createVAO(std::vector<Vertex>& vert,GLuint& vbo,GLuint& vao,int& numVertex);
	void cleanVAO(GLuint vbo,GLuint vao);

};
