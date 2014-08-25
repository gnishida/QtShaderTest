#pragma once

#include <QString>

class Shader
{
public:
	Shader() {}

	uint createProgram(const char *vertex_source, const char* fragment_source);

private:
	void loadTextFile(QString fileName, std::string& str);
	GLuint loadShader(std::string& source,uint mode);
	GLboolean printShaderInfoLog(GLuint shader, const char *str);
	GLboolean printProgramInfoLog(GLuint program);

private:
	GLuint program;
	GLuint vertex_shader;
	GLuint fragment_shader;
};

