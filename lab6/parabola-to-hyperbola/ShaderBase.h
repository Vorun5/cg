#pragma once

#include "inc.h"

class ShaderBase
{
public:
	ShaderBase(ShaderBase const&) = delete;
	ShaderBase& operator=(ShaderBase const&) = delete;

	void SetSource(GLsizei count, GLchar const** strings, GLint const* lengths);
	void SetSource(GLchar const* source, GLint length);
	void SetSource(GLchar const* source);

	void Compile();

	GLuint Attach(GLuint shader);
	GLuint Detach();

	void Delete();

	operator GLuint();

	GLuint GetParameter(GLenum name) const;

	std::string GetInfoLog() const;

protected:
	ShaderBase(GLuint shader = 0);

	~ShaderBase() = default;

private:
	GLuint m_shader;
};