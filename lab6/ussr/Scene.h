#pragma once
#include <glm/glm.hpp>
#include <vector>

class Scene
{
public:
	~Scene();

	void SetupFlag(float width, float height, int pixels = 1);

	void Draw();

	glm::vec3 GetFlagPos() {
		return m_flagPos;
	};
private:
	float m_radius,
		* m_arr;
	unsigned int* m_indices;

	glm::vec2* m_vertices;
	glm::vec3 m_flagPos;
	size_t m_verticesCount;
	GLuint m_buffer, m_VBO, m_EBO;
};