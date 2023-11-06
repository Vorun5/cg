#pragma once
#include "pch.h"

class Texture2D
{
public:
	void Setup(const std::string& texturePath),
			activate();

	int GetWidth() {
		return m_width;
	}

	int GetHeight() {
		return m_height;
	}
private:
	GLuint LoadTexture(const std::string& texturePath),
		m_texture;
	int m_width, m_height;
};