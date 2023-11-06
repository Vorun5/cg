#include "ProgramBase.h"

void ProgramBase::AttachShader(GLuint shader)
{
	if (m_program != 0)
	{
		glAttachShader(m_program, shader);
	}
}

void ProgramBase::DetachShader(GLuint shader)
{
	if (m_program != 0)
	{
		glDetachShader(m_program, shader);
	}
}

void ProgramBase::Link() const
{
	if (m_program != 0)
	{
		glLinkProgram(m_program);

		if (GetParameter(GL_LINK_STATUS) != GL_TRUE)
		{
			std::stringstream message;
			message << "Program " << m_program << " linkage failed: " << GetInfoLog();

			throw std::runtime_error(message.str());
		}
	}
}

void ProgramBase::Validate() const
{
	if (m_program != 0)
	{
		glValidateProgram(m_program);
	}
}

GLuint ProgramBase::Attach(GLuint program)
{
	auto tmp = m_program;
	m_program = program;
	return tmp;
}

GLuint ProgramBase::Detach()
{
	return Attach(0);
}

void ProgramBase::Delete()
{
	if (m_program != 0)
	{
		glDeleteProgram(m_program);
		m_program = 0;
	}
}

ProgramBase::operator GLuint() const
{
	return m_program;
}

GLint ProgramBase::GetParameter(GLenum name) const
{
	GLint value;
	glGetProgramiv(m_program, name, &value);
	return value;
}

void ProgramBase::SetParameter(GLenum name, GLint value)
{
	if (m_program != 0)
	{
		glProgramParameteri(m_program, name, value);
	}
}

std::string ProgramBase::GetInfoLog() const
{
	GLint length = GetParameter(GL_INFO_LOG_LENGTH);
	if (length > 0)
	{
		std::vector<char> buffer(length);
		glGetProgramInfoLog(m_program, length, &length, &buffer[0]);
		std::string log(&buffer[0], length - 1);
		return log;
	}

	return {};
}

GLint ProgramBase::GetUniformLocation(GLchar const* name) const
{
	return glGetUniformLocation(m_program, name);
}

ProgramBase::ProgramBase(GLuint program)
	: m_program(program)
{
}