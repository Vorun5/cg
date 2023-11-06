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
	static float inline m_vertices[12][3] = {
		{ -1, -1, 0 },
		{ 0, -1, +1 },
		{ +1, -1, 0 },
		{ 0, -1, -1 },
		{ -1, 0, -1 },
		{ +1, 0, -1 },
		{ +1, +1, 0 },
		{ +1, 0, +1 },
		{ 0, +1, -1 },
		{ -1, +1, 0 },
		{ 0, +1, +1 },
		{ -1, 0, +1 },
	};
	unsigned char m_squareFaces[6][4] = {
		{11, 1, 7, 10},
		{4, 8, 5, 3},
		{7, 2, 5, 6},
		{0, 11, 9, 4},
		{1, 0, 3, 2},
		{10, 6, 8, 9},
	};
	unsigned char m_triangularFaces[8][3] = {
		{ 11, 10, 9 },
		{ 10, 7, 6 },
		{ 0, 1, 11 },
		{ 1, 2, 7 },
		{ 4, 9, 8 },
		{ 8, 6, 5 },
		{ 0, 4, 3 },
		{ 3, 5, 2 },
	};

	void DrawTriangles(const bool front) const;
	void DrawSquares(const bool front) const;
};