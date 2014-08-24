#version 150
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0)in vec3 vertex;
layout(location = 1)in vec3 color;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec3 uv;

out vec3 varColor;
out vec3 varNormal;

uniform mat4 mvpMatrix;

void main()
{
	varColor = color;
	varNormal = normalize(normal);

	//gl_Position = mvpMatrix * vec4(vertex, 1.0);
	gl_Position = gl_NormalMatrix * vec4(vertex, 1.0);
}