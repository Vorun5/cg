#include "inc.h"
#include "ShaderLoader.h"

GLuint ShaderLoader::LoadShader(GLenum shaderType, char const* fileName, GLuint shaderId)
{
	std::ifstream stream(fileName);
	if (!stream.is_open())
	{
		throw std::runtime_error("Failed to read from file");
	}

	return LoadShader(shaderType, stream, shaderId);
}

GLuint ShaderLoader::LoadShader(GLenum shaderType, std::istream& input, GLuint shaderId)
{
	std::stringstream stream;
	stream << input.rdbuf();

	return LoadShader(shaderType, stream.str(), shaderId);
}

GLuint ShaderLoader::LoadShader(GLenum shaderType, std::string const& source, GLuint shaderId)
{
	Shader shader(shaderId);
	if (!shader)
	{
		shader.Create(shaderType);
	}
	shader.SetSource(source.c_str());

	return shader.Detach();
}