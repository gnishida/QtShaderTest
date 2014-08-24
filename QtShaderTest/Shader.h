#pragma once

#include <QString>

class Shader
{
public:
	Shader() {}

	uint createProgram(const char *vertex_source, const char* fragment_source);

	void loadTextFile(QString fileName, std::string& str);
	uint loadShader(std::string& source,uint mode);
	bool printShaderInfoLog(GLuint shader, const char *str);
	bool printProgramInfoLog(GLuint program);

public:
	uint program;
	uint vertex_shader;
	uint fragment_shader;
};

