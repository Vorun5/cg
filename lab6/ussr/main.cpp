#include <iostream>
#include "Window.h"
#include "CGLFWInitializer.h"
#include <SDL2/SDL_error.h>

int main()
{
	try {
		CGLFWInitializer initGLFW;
		Window window{ 800, 600, "USSR" };
		window.Run();
	}
	catch (std::runtime_error& ex) {
		std::cout << ex.what();
		return 1;
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
		return 1;
	}
	catch (GLenum& ex) {
		std::cout << ex;
		return 1;
	}
	catch (SDL_errorcode& error) {
		std::cout << SDL_Error(error);
		return 1;
	}
	return 0;
}