#pragma once
#include "ThorSide.h"
#include <vector>

class Thor
{
public:
	Thor(float R = 0.7f, float r = 0.25f, int segmentsA = 100, int segmentsB = 200);
	
	void Draw() const;

private:
	glm::vec3 m_thorColor = { 0.4f, 0.4f, 1.0f };
	glm::vec4 m_lightColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	float m_shininess = 20.0f;
	std::vector<ThorSide> m_sides;
	float m_R, m_r;
	int m_segmentsA, m_segmentsB;

	float m_drawingDegree = 360;

	glm::vec3 CalculateCoordinates(float angleA, float angleB);
	glm::vec3 CalculateNormalCoordinates(float angleA, float angleB);
};