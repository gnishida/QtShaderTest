#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 texCoord;

// varying variables
out vec3 varColor;
out vec3 varTexCoord;
out vec3 varNormal;

// uniform variables
uniform int mode;	// 1 -- color / 2 -- texture
uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform vec3 lightDir;

void main(){
	varColor = color;
	varTexCoord = texCoord;
	
	//varNormal = normalize(normal);
	varNormal = normalize(mvMatrix * vec4(normal, 0.0)).xyz;

	gl_Position = mvpMatrix * vec4(position, 1.0);
}