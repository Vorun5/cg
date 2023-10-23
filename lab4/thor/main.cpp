#include <iostream>
#include "Window.h"
#include "CGLFWInitializer.h"

int main()
{
	CGLFWInitializer initGLFW;
	Window window{ 1000, 1000, "Thor" };
	window.Run();
}