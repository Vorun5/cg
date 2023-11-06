#pragma once

#include "ShaderImpl.h"

class ShaderLoader
{
public:
	static GLuint LoadShader(GLenum shaderType, char const* fileName, GLuint shaderId = 0);
	static GLuint LoadShader(GLenum shaderType, std::istream& input, GLuint shaderId = 0);
	static GLuint LoadShader(GLenum shaderType, std::string const& source, GLuint shaderId = 0);
};