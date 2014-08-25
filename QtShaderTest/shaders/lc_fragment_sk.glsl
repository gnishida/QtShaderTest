#version 420
#extension GL_EXT_gpu_shader4 : enable

in vec3 outColor;
in vec3 outUV;
in vec3 origVertex;// L

in vec3 varyingNormal;
in vec4 varyingLightVertexPosition;//position respect the camera view

out vec4 outputF;

uniform int mode;
uniform sampler2D tex0;
uniform sampler2DArray tex_3D;
//uniform sampler3D tex_3D;

uniform vec4 terrain_size;//remove if terrainMode=2 removed
uniform sampler2D terrain_tex;

uniform sampler2D shadowMap;
uniform int shadowState;
 
uniform vec3 lightDir;
uniform mat4 light_mvpMatrix;
uniform mat4 light_biasMatrix;	//transfrom to [0,1] tex coordinates

uniform float waterMove;

const float ambientColor=0.1;
const float diffuseColor=1.0;
const float specularColor=1.0;

vec3 terrainMode3Colors[] = vec3[5]( 
   vec3( 0xf0/255.0, 0xed/255.0, 0xe5/255.0 ), // 7 mid river
   vec3( 0xca/255.0 ,0xdf/255.0, 0xaa/255.0 ), // 8 green
   vec3( 0xdf/255.0, 0xd9/255.0, 0xc3/255.0 ), // 9 coast
   vec3( 0xe9/255.0, 0xe5/255.0, 0xdc/255.0 ), //10 flat
   vec3( 0x50/255.0, 0x44/255.0, 0x43/255.0 ) //11 mountain 504443
);

vec2 poissonDisk4[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

vec2 poissonDisk16[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);

// Returns a random number based on a vec3 and an int.
float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

float shadowCoef(){
	vec4 shadow_coord2=light_mvpMatrix*vec4(origVertex,1.0);
	vec3 ProjCoords = shadow_coord2.xyz / shadow_coord2.w;
    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;
	
	/// D
	bool HDShadow=true;
	float visibility=1.0f;
	if(HDShadow==true){
		// HDShadow
		for (int i=0;i<8;i++){
			int index = int(16.0*random(origVertex.xyz, i))%16;
			if ( texture2D( shadowMap, UVCoords + poissonDisk16[index]/3500.0 ).z  <  z ){
				visibility-=0.1;
			}
		}
	}else{
		// Low Shadow
		for (int i=0;i<4;i++){
			int index = int(4.0*random(origVertex.xyz, i))%4;
			if ( texture2D( shadowMap, UVCoords + poissonDisk4[index]/3500.0 ).z  <  z ){
				visibility-=0.2;
			}
		}

	}
	return visibility;
}

float facade(vec2 coordFac,vec2 maxFac,int windNumber){
	float intVal=1.0f;
	
	// SIDES
	if(coordFac.x<2.5||coordFac.y<2.5){
		//return 0;
		intVal= smoothstep(1.5,2.5,min(coordFac.x,coordFac.y));
	}
	if(coordFac.x>maxFac.x-2.5||coordFac.y>maxFac.y-2.5){
		float coord=min(maxFac.x-coordFac.x,maxFac.y-coordFac.y);
		intVal= min(intVal,smoothstep(1.5,2.5,coord));
	}
	if(intVal==0)
		return 0;
	// WINDOWS
	int numSt=int(ceil(maxFac.y*0.26f));//3.0m
	int numWin=int(ceil(maxFac.x*0.26f));
	//if(int(numWin*coordFac.x/maxFac.x)%2==0)
	//	return 1.0;
	
	int currS=int((numSt*coordFac.y)/maxFac.y);
	if(currS==0||currS==numSt-1)//side windows
		return intVal;
	//float currS=(numSt*coordFac.y)/maxFac.y;
	//if(currS<2.0)//first floor
	//	return max(intVal-(2.0-currS),0);
	int currWind=int((numWin*coordFac.x)/maxFac.x);
	if(currWind==0||currWind==numWin-1)//side windows
		return intVal;
	
	return intVal*texture( tex_3D, vec3(vec2(numWin,numSt)*coordFac.xy/maxFac.xy,7.0) )[windNumber];//6 window
	//return intVal;

}//

void main(){

	outputF =vec4(outColor,1.0);

	// TEXTURE
	if((mode&0xFF)==2){// tex
		outputF = texture( tex0, outUV.rg );
	}

	// LIGHTING
	vec4 ambientIllumination=vec4(0.05,0.05,0.05,0.0);
	vec4 diffuseIllumination=vec4(0.95,0.95,0.95,1.0);
	if(((mode&0x0200)==0x0200)||((mode&0xFF)==0x03)){//terran also gets lighting
		vec3 normal = varyingNormal;
		if(((mode&0x0FF)==0x05)||((mode&0xFF)==0x06))//seems that it needs it
			normal=normalize(normal);
		ambientIllumination = ambientColor*vec4(1.0,1.0,1.0,1.0);
		diffuseIllumination = (diffuseColor*vec4(1.0,1.0,1.0,1.0)) * max(0.0, dot(-lightDir, normal));
	}

	// SHADOW Disable
	if(shadowState==0){// 0 SHADOW Disable
		outputF=(ambientIllumination+diffuseIllumination)*outputF;
	}
}//

