#include "VBORenderManager.h"

	VBORenderManager::VBORenderManager(){
	}

	VBORenderManager::~VBORenderManager() {
		Shader::cleanShaders();
	}

	void VBORenderManager::init(){
		// init program shader
		program=Shader::initShader(QString("shaders/lc_vertex_sk.glsl"),QString("shaders/lc_fragment_sk.glsl"));
		glUseProgram(program);

		nameToTexId[""]=0;

		printf("VBORenderManager\n");

	}//

	GLuint VBORenderManager::loadTexture(const QString fileName,bool mirrored){
		GLuint texId;
		if(nameToTexId.contains(fileName)){
			texId=nameToTexId[fileName];
		}else{
			texId=VBOUtil::loadImage(fileName,mirrored);
			nameToTexId[fileName]=texId;
		}
		return texId;
	}//

	GLuint VBORenderManager::loadArrayTexture(QString texName,std::vector<QString> fileNames){
		GLuint texId;
		if(nameToTexId.contains(texName)){
			texId=nameToTexId[texName];
		}else{
			texId=VBOUtil::loadImageArray(fileNames);
			nameToTexId[texName]=texId;
		}
		return texId;
	}

	// ATRIBUTES
	// 0 Vertex
	// 1 Color
	// 2 Normal
	// 3 UV

	// UNIFORMS
	// 0 mode
	// 1 tex0

	bool VBORenderManager::createVAO(std::vector<Vertex>& vert,GLuint& vbo,GLuint& vao,int& numVertex){
		glGenVertexArrays(1,&vao);
		glBindVertexArray(vao);
		// Crete VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vert.size(), vert.data(), GL_STATIC_DRAW);
	
		// Configure the attributes in the VAO.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(3*sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(6*sizeof(float)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(9*sizeof(float)));


		// Bind back to the default state.
		glBindVertexArray(0); 
		glBindBuffer(GL_ARRAY_BUFFER,0);
		
	
		// clean space
		numVertex=vert.size();
		//vert.clear();
		return true;
	}//

	void VBORenderManager::renderVAO(RenderSt& renderSt,bool cleanVertex){
		//printf("renderVAO numVert %d texNum %d vao %d numVertVert %d\n",renderSt.numVertex,renderSt.texNum,renderSt.vao,renderSt.vertices.size());
		// 1. Create if necessary
		if(renderSt.numVertex!=renderSt.vertices.size()&&renderSt.vertices.size()>0){
			if(renderSt.numVertex!=-1){
				cleanVAO(renderSt.vbo,renderSt.vao);
			}
			// generate vao/vbo
			createVAO(renderSt.vertices,renderSt.vbo,renderSt.vao,renderSt.numVertex);
			if(cleanVertex)
				renderSt.vertices.clear();
		}
		// 2. Render
		// 2.1 TEX
		int mode=renderSt.shaderMode;
		if((mode&mode_TexArray)==mode_TexArray){
			// MULTI TEX
			mode=mode&(~mode_TexArray);//remove tex array bit
			glActiveTexture(GL_TEXTURE8);

			glBindTexture(GL_TEXTURE_2D,0); 
			glBindTexture(GL_TEXTURE_2D_ARRAY, renderSt.texNum);
			glActiveTexture(GL_TEXTURE0);
			glUniform1i (glGetUniformLocation (program, "tex_3D"), 8);
		}else{
			glBindTexture(GL_TEXTURE_2D, renderSt.texNum);
		}
		// 2.2 mode
		//if(renderSt.texNum==0){
			//glUniform1i (glGetUniformLocation (program, "mode"), 1|(renderSt.shaderMode&0xFF00));//MODE: same modifiers but just color (renderSt.shaderMode&0xFF00)
		//}else{
			glUniform1i (glGetUniformLocation (program, "mode"), mode);
		//}

		glUniform1i (glGetUniformLocation (program, "tex0"), 0);//tex0: 0

		glBindVertexArray(renderSt.vao);
		glDrawArrays(renderSt.geometryType,0,renderSt.numVertex);
		glBindVertexArray(0);
	}

	void VBORenderManager::renderAll(bool cleanVertex){
		//vboTerrain.render(editionMode,mousePos3D);
		//vboWater.render(*this);
		
		////////////////////////
		// 1. STATIC
		QHash<QString,renderGrid>::iterator statcIt;
		// 1.1 iterate over geoNames
		for (statcIt = geoName2StaticRender.begin(); statcIt != geoName2StaticRender.end(); ++statcIt){
			printf("Render: %s\n",statcIt.key().toAscii().constData());
			// 1.1.1 iterate over textures
			renderGrid::iterator i;
			for (i = statcIt.value().begin(); i != statcIt.value().end(); ++i){
				renderVAO(i.value(),cleanVertex);
			}
		}

	}//

	

	void VBORenderManager::cleanVAO(GLuint vbo,GLuint vao){
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}//


	///////////////////////////////////////////////////////////////////
	// STATIC
	bool VBORenderManager::addStaticGeometry(QString geoName,std::vector<Vertex>& vert,QString texName,GLenum geometryType,int shaderMode){
		if(vert.size()<=0)
			return false;
		GLuint texId;
		if(nameToTexId.contains(texName)){
			texId=nameToTexId[texName];
		}else{
			printf("load img %s\n",texName.toAscii().constData());
			texId=VBOUtil::loadImage(texName);
			nameToTexId[texName]=texId;
		}
		
		if(geoName2StaticRender.contains(geoName)){
			// 1.1 If already in manager
			if(geoName2StaticRender[geoName].contains(texId)){
				if(geoName2StaticRender[geoName][texId].vertices.size()==0){
					//1.1.1 if also contains texture and the number of vertex=0--> vao created--> remove
					cleanVAO(geoName2StaticRender[geoName][texId].vbo,geoName2StaticRender[geoName][texId].vao);
					geoName2StaticRender[geoName][texId]=RenderSt(texId,vert,geometryType,shaderMode);
				}else{
					//1.1.1 if also contains texture and the number of vertex!=0--> vao no created--> just append
					if(geometryType==GL_TRIANGLE_STRIP){
						//vert.insert(vert.begin(),vert.front());
						vert.insert(vert.begin(),geoName2StaticRender[geoName][texId].vertices.back());
						vert.insert(vert.begin(),geoName2StaticRender[geoName][texId].vertices.back());
					}
					geoName2StaticRender[geoName][texId].vertices.insert(geoName2StaticRender[geoName][texId].vertices.end(),vert.begin(),vert.end());
				}
			}else{
				geoName2StaticRender[geoName][texId]=RenderSt(texId,vert,geometryType,shaderMode);
			}
			//printf("--> YES in manager %s\n",geoName.toAscii().constData());
		}else{
			// 1.2 No yet in manager
			geoName2StaticRender[geoName][texId]=RenderSt(texId,vert,geometryType,shaderMode);
			//renderStaticGeometry(geoName);
			//printf("--> It was not yet in manager %s\n",geoName.toAscii().constData());
		}
		return true;
	}//

	bool VBORenderManager::checkIfGeoNameInUse(QString geoName){
		return (geoName2StaticRender.contains(geoName));
	}//


	bool VBORenderManager::removeStaticGeometry(QString geoName){
		if(geoName2StaticRender.contains(geoName)){
			// iterate and remove
			renderGrid::iterator i;
			for (i = geoName2StaticRender[geoName].begin(); i != geoName2StaticRender[geoName].end(); ++i){
				cleanVAO(geoName2StaticRender[geoName][i.key()].vbo,geoName2StaticRender[geoName][i.key()].vao);
			}
			geoName2StaticRender[geoName].clear();
			geoName2StaticRender.remove(geoName);
		}else{
			//printf("ERROR: Remove Geometry %s but it did not exist\n",geoName.toAscii().constData());
			return false;
		}

		return true;
	}//

	void VBORenderManager::renderStaticGeometry(QString geoName){

		if(geoName2StaticRender.contains(geoName)){
			// iterate and remove
			renderGrid::iterator i;
			for (i = geoName2StaticRender[geoName].begin(); i != geoName2StaticRender[geoName].end(); ++i){
				renderVAO(i.value(),false);
			}
		}else{
			//printf("ERROR: Render Geometry %s but it did not exist\n",geoName.toAscii().constData());
			return;
		}
	}//

	
