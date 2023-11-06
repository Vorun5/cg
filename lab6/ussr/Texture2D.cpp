#include "Texture2D.h"
#include "SDL2/SDL_image.h"

void Texture2D::Setup(const std::string& texturePath)
{
	m_texture = LoadTexture(texturePath);
}

void Texture2D::activate()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

GLuint Texture2D::LoadTexture(const std::string& texturePath)
{
	// --- LOAD_IMAGE
	SDL_Surface* surface;
	surface = IMG_Load(texturePath.c_str());
	if (!surface) {
		std::cout << IMG_GetError();
	}
	SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
	SDL_Surface* convertedSurface = SDL_ConvertSurface(surface, format, 0);
	// --- LOAD_IMAGE

	m_height = convertedSurface->h, m_width = convertedSurface->w;

	//glActiveTexture(GL_TEXTURE0 + txtr);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	auto err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << err;
		std::cout << surface->pixels;
	}
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGBA8, GL_UNSIGNED_BYTE, surface->pixels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, convertedSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	err = glGetError();

	glBindTexture(GL_TEXTURE_2D, 0);


	// --- FREE_IMAGE
	SDL_FreeSurface(convertedSurface);
	SDL_FreeFormat(format);
	SDL_FreeSurface(surface);

	return texture;
}