#include "pch.h"
#include "Thor.h"

Thor::Thor(float R, float r, int segmentsA, int segmentsB)
	:m_R(R)
	,m_r(r)
	,m_segmentsA(segmentsA)
	,m_segmentsB(segmentsB)
{

	float deltaA = m_drawingDegree / m_segmentsA;
	float deltaB = m_drawingDegree / m_segmentsB;

	for (float angleA = 0.0f; angleA <= m_drawingDegree; angleA += deltaA) {
		for (float angleB = 0.0f; angleB <= m_drawingDegree; angleB += deltaB) {
			m_sides.push_back({
				CalculateCoordinates(angleA, angleB),
				CalculateCoordinates(angleA, angleB + deltaB),
				CalculateCoordinates(angleA + deltaA, angleB + deltaB),
				CalculateCoordinates(angleA + deltaA, angleB),
				CalculateNormalCoordinates(angleA, angleB),
				CalculateNormalCoordinates(angleA, angleB + deltaB),
				CalculateNormalCoordinates(angleA + deltaA, angleB + deltaB),
				CalculateNormalCoordinates(angleA + deltaA, angleB)
			});
		}
	}
}

/*
	(xα,β)=(R+r*cosA)*cosB
	(yα,β)=(R+r*cosA)*sinB
	(zα,β)=r*sinA
*/
glm::vec3 Thor::CalculateCoordinates(float angleA, float angleB) {
	const float radiansA = glm::radians(angleA);
	const float radiansB = glm::radians(angleB);

	return glm::vec3(
		(m_R + (m_r * cos(radiansA))) * cos(radiansB),
		(m_R + (m_r * cos(radiansA))) * sin(radiansB),
		m_r * sin(radiansA)
	);
};

glm::vec3 Thor::CalculateNormalCoordinates(float angleA, float angleB) {
	const float radiansA = glm::radians(angleA);
	const float radiansB = glm::radians(angleB);

	return glm::vec3(
		cos(radiansB) * cos(radiansA),
		sin(radiansB) * cos(radiansA),
		sin(radiansA)
	);
};


void Thor::Draw() const
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_lightColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

	// Включение режима отбраковки граней
	glEnable(GL_CULL_FACE);
	//  Эта строка устанавливает, что будут отсекаться задние (back) грани полигонов. 
	glCullFace(GL_BACK);

	glColor3f(m_thorColor.r, m_thorColor.g, m_thorColor.b);
	glBegin(GL_QUADS);

	for (auto& side : m_sides) {
		glNormal3f(side.n1.x, side.n1.y, side.n1.z);
		glVertex3f(side.p1.x, side.p1.y, side.p1.z);

		glNormal3f(side.n2.x, side.n2.y, side.n2.z);
		glVertex3f(side.p2.x, side.p2.y, side.p2.z);

		glNormal3f(side.n3.x, side.n3.y, side.n3.z);
		glVertex3f(side.p3.x, side.p3.y, side.p3.z);

		glNormal3f(side.n4.x, side.n4.y, side.n4.z);
		glVertex3f(side.p4.x, side.p4.y, side.p4.z);
	}

	glEnd();
}