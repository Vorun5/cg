#pragma once

#include "ShaderBase.h"

template <bool t_managed>
class ShaderImpl : public ShaderBase
{
public:
	ShaderImpl(GLuint shader = 0)
		: ShaderBase(shader)
	{
	}

	ShaderImpl& operator=(GLuint shader)
	{
		if (t_managed)
		{
			Delete();
		}
		Attach(shader);

		return *this;
	}

	GLuint Create(GLenum type)
	{
		if (t_managed)
		{
			Delete();
		}
		GLuint shader = glCreateShader(type);
		Attach(shader);

		return shader;
	}

	~ShaderImpl()
	{
		if (t_managed)
		{
			Delete();
		}
	}
};

using Shader = ShaderImpl<true>;
using ShaderHandle = ShaderImpl<false>;