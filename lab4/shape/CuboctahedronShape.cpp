#include "pch.h"
#include "CuboctahedronShape.h"

CuboctahedronShape::CuboctahedronShape(float size)
    : m_size(size)
{
    SetSideColor(CuboctahedronSide::FRONT_SQUARE, 247, 176, 76);
    SetSideColor(CuboctahedronSide::BACK_SQUARE, 242, 153, 74);
    SetSideColor(CuboctahedronSide::RIGHT_SQUARE, 242, 201, 76);
    SetSideColor(CuboctahedronSide::LEFT_SQUARE, 39, 174, 96);
    SetSideColor(CuboctahedronSide::UPPER_SQUARE, 45, 156, 219);
    SetSideColor(CuboctahedronSide::LOWER_SQUARE, 187, 107, 217);
    SetSideColor(CuboctahedronSide::FRONT_UPPER_RIGHT_TRIANGULAR, 86, 204, 242);
    SetSideColor(CuboctahedronSide::FRONT_UPPER_LEFT_TRIANGULAR, 111, 207, 151);
    SetSideColor(CuboctahedronSide::FRONT_LOWER_LEFT_TRIANGULAR, 38, 55, 215);
    SetSideColor(CuboctahedronSide::FRONT_LOWER_RIGHT_TRIANGULAR, 246, 145, 236);
    SetSideColor(CuboctahedronSide::BACK_UPPER_RIGHT_TRIANGULAR, 164, 147, 89);
    SetSideColor(CuboctahedronSide::BACK_UPPER_LEFT_TRIANGULAR, 89, 164, 137);
    SetSideColor(CuboctahedronSide::BACK_LOWER_LEFT_TRIANGULAR, 158, 103, 103);
    SetSideColor(CuboctahedronSide::BACK_LOWER_RIGHT_TRIANGULAR, 146, 164, 161);
}

void CuboctahedronShape::DrawSquares() const
{

}

void CuboctahedronShape::DrawTriangles() const
{

}


void CuboctahedronShape::Draw() const
{
	static constexpr float vertices[12][3] = {
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

	static constexpr unsigned char squareFaces[6][4] = {
		{11, 1, 7, 10},
		{4, 8, 5, 3},
		{7, 2, 5, 6},
		{0, 11, 9, 4},
		{1, 0, 3, 2},
		{10, 6, 8, 9},
	};

	static constexpr unsigned char triangularFaces[8][3] = {
		{ 11, 10, 9 },
		{ 10, 7, 6 },
		{ 0, 1, 11 },
		{ 1, 2, 7 },
		{ 4, 9, 8 },
		{ 8, 6, 5 },
		{ 0, 4, 3 },
		{ 3, 5, 2 },
	};

	static size_t const triangularFaceCount = sizeof(triangularFaces) / sizeof(*triangularFaces);
	static size_t const squareFaceCount = sizeof(squareFaces) / sizeof(*squareFaces);

	glEnable(GL_COLOR_MATERIAL);
	// Цвет вершины будет управлять диффузным и фоновым цветом материала
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_lightColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);


	glBegin(GL_TRIANGLES);
	{
		for (size_t face = 0; face < triangularFaceCount; ++face)
		{
			glColor4ubv(m_sideColors[face + 6]);
			const unsigned char* facePoints = triangularFaces[face];

			// получаем вершины очередной грани куба
			auto p0 = glm::make_vec3(vertices[facePoints[0]]);
			auto p1 = glm::make_vec3(vertices[facePoints[1]]);
			auto p2 = glm::make_vec3(vertices[facePoints[2]]);

			// Вычисляем координаты вершин куба с учетом его размера
			p0 *= m_size * m_size;
			p1 *= m_size * m_size;
			p2 *= m_size * m_size;

			// Вычисляем нормаль к грани куба через
			// векторное произведение его смежных сторон
			auto v01 = p1 - p0;
			auto v02 = p2 - p0;
			auto normal = glm::normalize(glm::cross(v01, v02));

			glNormal3fv(glm::value_ptr(normal));

			glVertex3fv(glm::value_ptr(p0));
			glVertex3fv(glm::value_ptr(p1));
			glVertex3fv(glm::value_ptr(p2));
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		for (size_t face = 0; face < squareFaceCount; ++face)
		{
			glColor4ubv(m_sideColors[face]);
			const unsigned char* facePoints = squareFaces[face];

			// получаем вершины очередной грани куба
			auto p0 = glm::make_vec3(vertices[facePoints[0]]);
			auto p1 = glm::make_vec3(vertices[facePoints[1]]);
			auto p2 = glm::make_vec3(vertices[facePoints[2]]);
			auto p3 = glm::make_vec3(vertices[facePoints[3]]);
			
			// Вычисляем координаты вершин куба с учетом его размера
			p0 *= m_size * m_size;
			p1 *= m_size * m_size;
			p2 *= m_size * m_size;
			p3 *= m_size * m_size;

			// Вычисляем нормаль к грани куба через
			// векторное произведение его смежных сторон
			auto v01 = p1 - p0;
			auto v02 = p2 - p0;
			auto normal = glm::normalize(glm::cross(v01, v02));

			glNormal3fv(glm::value_ptr(normal));

			glVertex3fv(glm::value_ptr(p0));
			glVertex3fv(glm::value_ptr(p1));
			glVertex3fv(glm::value_ptr(p2));
			glVertex3fv(glm::value_ptr(p3));
		}
	}
	glEnd();
}

void CuboctahedronShape::SetSideColor(CuboctahedronSide side, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
    const size_t index = static_cast<size_t>(side);
    m_sideColors[index][0] = r;
    m_sideColors[index][1] = g;
    m_sideColors[index][2] = b;
    m_sideColors[index][3] = a;
}
