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

void CuboctahedronShape::DrawSquares(const bool front) const
{
	static size_t const squareFaceCount = sizeof(m_squareFaces) / sizeof(*m_squareFaces);

	glBegin(GL_QUADS);
	{
		for (size_t face = 0; face < squareFaceCount; ++face)
		{
			glColor4ubv(m_sideColors[face]);

			const unsigned char* facePoints = m_squareFaces[face];

			// получаем вершины очередной грани куба
			auto p0 = glm::make_vec3(m_vertices[facePoints[0]]);
			auto p1 = glm::make_vec3(m_vertices[facePoints[1]]);
			auto p2 = glm::make_vec3(m_vertices[facePoints[2]]);
			auto p3 = glm::make_vec3(m_vertices[facePoints[3]]);

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
			if (!front) normal = -normal;

			glNormal3fv(glm::value_ptr(normal));
			glVertex3fv(glm::value_ptr(p0));
			glVertex3fv(glm::value_ptr(p1));
			glVertex3fv(glm::value_ptr(p2));
			glVertex3fv(glm::value_ptr(p3));
		}
	}
	glEnd();
}

void CuboctahedronShape::DrawTriangles(const bool front) const
{
	static size_t const triangularFaceCount = sizeof(m_triangularFaces) / sizeof(*m_triangularFaces);

	glBegin(GL_TRIANGLES);
	{
		for (size_t face = 0; face < triangularFaceCount; ++face)
		{
			glColor4ubv(m_sideColors[face + 6]);
			const unsigned char* facePoints = m_triangularFaces[face];

			// получаем вершины очередной грани куба
			auto p0 = glm::make_vec3(m_vertices[facePoints[0]]);
			auto p1 = glm::make_vec3(m_vertices[facePoints[1]]);
			auto p2 = glm::make_vec3(m_vertices[facePoints[2]]);

			// Вычисляем координаты вершин куба с учетом его размера
			p0 *= m_size * m_size;
			p1 *= m_size * m_size;
			p2 *= m_size * m_size;

			auto normal = glm::normalize(glm::triangleNormal(p0, p1, p2));
			if (!front) normal = -normal;
			
			glNormal3fv(glm::value_ptr(normal));
			glVertex3fv(glm::value_ptr(p0));
			glVertex3fv(glm::value_ptr(p1));
			glVertex3fv(glm::value_ptr(p2));
		}
	}
	glEnd();
}

void CuboctahedronShape::Draw() const
{
	glEnable(GL_COLOR_MATERIAL);
	// Цвет вершины будет управлять диффузным и фоновым цветом материала
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_lightColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);

	// Включем режим отбраковки передних граней	
	glCullFace(GL_FRONT);
	DrawTriangles(false);
	DrawSquares(false);

	// Включаем режим отбраковки внутрениих граней
	glCullFace(GL_BACK);
	DrawTriangles(true);
	DrawSquares(true);

}

void CuboctahedronShape::SetSideColor(CuboctahedronSide side, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
    const size_t index = static_cast<size_t>(side);
    m_sideColors[index][0] = r;
    m_sideColors[index][1] = g;
    m_sideColors[index][2] = b;
    m_sideColors[index][3] = a;
}
