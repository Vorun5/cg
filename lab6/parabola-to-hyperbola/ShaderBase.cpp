#include "ShaderBase.h"

void ShaderBase::SetSource(GLsizei count, GLchar const** strings, GLint const* lengths)
{
	if (m_shader != 0)
	{
		glShaderSource(m_shader, count, strings, lengths);
	}
}

void ShaderBase::SetSource(GLchar const* source, GLint length)
{
	GLchar const** ppSource = &source;
	SetSource(1, ppSource, &length);
}

void ShaderBase::SetSource(GLchar const* source)
{
	GLchar const** ppSource = &source;
	SetSource(1, ppSource, nullptr);
}

void ShaderBase::Compile()
{
	if (m_shader != 0)
	{
		glCompileShader(m_shader);

		if (GetParameter(GL_COMPILE_STATUS) != GL_TRUE)
		{
			std::stringstream message;
			message << "Shader " << m_shader << " compilation failed: " << GetInfoLog();

			throw std::runtime_error(message.str());
		}
	}
}

GLuint ShaderBase::Attach(GLuint shader)
{
	auto tmp = m_shader;
	m_shader = shader;
	return tmp;
}

GLuint ShaderBase::Detach()
{
	return Attach(0);
}

void ShaderBase::Delete()
{
	if (m_shader != 0)
	{
		glDeleteShader(m_shader);
		m_shader = 0;
	}
}

ShaderBase::operator GLuint()
{
	return m_shader;
}

GLuint ShaderBase::GetParameter(GLenum name) const
{
	GLint value;
	glGetShaderiv(m_shader, name, &value);
	return value;
}

std::string ShaderBase::GetInfoLog() const
{
	GLint length = GetParameter(GL_INFO_LOG_LENGTH);
	if (length > 0)
	{
		std::vector<char> buffer(length);
		glGetShaderInfoLog(m_shader, length, &length, &buffer[0]);
		std::string log(&buffer[0]);
		return log;
	}

	return {};
}

ShaderBase::ShaderBase(GLuint shader)
	: m_shader(shader)
{
}