#pragma once

#include "ProgramBase.h"

template <bool t_managed>
class ProgramImpl : public ProgramBase
{
public:
	ProgramImpl(GLuint program = 0)
		: ProgramBase(program)
	{
	}

	ProgramImpl& operator=(GLuint program)
	{
		if (t_managed)
		{
			Delete();
		}
		Attach(program);

		return *this;
	}

	GLuint Create()
	{
		if (t_managed)
		{
			Delete();
		}
		auto program = glCreateProgram();
		Attach(program);

		return program;
	}

	~ProgramImpl()
	{
		if (t_managed)
		{
			Delete();
		}
	}
};

using Program = ProgramImpl<true>;
using ProgramHandle = ProgramImpl<false>;