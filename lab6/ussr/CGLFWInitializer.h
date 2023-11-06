#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>


class CGLFWInitializer
{
public:
	CGLFWInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	CGLFWInitializer(const CGLFWInitializer&) = delete;
	CGLFWInitializer& operator=(const CGLFWInitializer&) = delete;

	~CGLFWInitializer()
	{
		glfwTerminate();
	}
};