#version 420

layout(location = 0)in vec3 vertex;
layout(location = 1)in vec3 color;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec3 uv;


out vec3 outColor;
out vec3 outUV;
out vec3 origVertex;// L

out vec3 varyingNormal;

// UNIFORM
uniform int mode;

// MODE 1--> color
// MODE 2--> texture
// MODE 3--> terrain
// MODE 4--> water
// MODE 5--> model obj: one color
// MODE 6--> model obj: texture

         // // MODE 9--> hatch
		// // MODE 10--> hatch

//0x0100 --> adapt terrain
//0x0200 --> lighting

uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

uniform mat4 light_mvpMatrix;
uniform mat4 light_biasMatrix;	//transfrom to [0,1] tex coordinates
//uniform vec3 lightPosition;  //model-space

uniform int shadowState;
// 0 DISABLE
// 1 SHADOW Render Normal
// 2 SHADOW Render from light

// terrain
uniform vec4 terrain_size;
uniform sampler2D terrain_tex;

// model
uniform vec3 justOneColor;
uniform mat4 modelTransf;

void main(){
	outColor=color;
	outUV=uv;
	origVertex=vertex;

	//////////////////////////////////////
	// LIGHTING
	if((mode&0x0200)==0x0200){
		//varyingNormal=normalMatrix*normal;
		varyingNormal=normalize(normal);//here to avoid doing it in the fragment
	}

	gl_Position = mvpMatrix * vec4(origVertex,1.0);

}