#pragma once
#include <vector>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>

enum class CuboctahedronSide
{
	FRONT_SQUARE,
	BACK_SQUARE,
	RIGHT_SQUARE,
	LEFT_SQUARE,
	UPPER_SQUARE,
	LOWER_SQUARE,
	FRONT_UPPER_RIGHT_TRIANGULAR,
	FRONT_UPPER_LEFT_TRIANGULAR,
	FRONT_LOWER_LEFT_TRIANGULAR,
	FRONT_LOWER_RIGHT_TRIANGULAR,
	BACK_UPPER_RIGHT_TRIANGULAR,
	BACK_UPPER_LEFT_TRIANGULAR,
	BACK_LOWER_LEFT_TRIANGULAR,
	BACK_LOWER_RIGHT_TRIANGULAR
};

class CuboctahedronShape
{
public:
	explicit CuboctahedronShape(float size = 0.8f);
	void Draw() const;
	void SetSideColor(CuboctahedronSide side, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);

private:
	float m_size;
	float m_shininess = 1.0f;
	glm::vec4 m_lightColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLubyte m_sideColors[14][4];

	void DrawTriangles() const;
	void DrawSquares() const;
};