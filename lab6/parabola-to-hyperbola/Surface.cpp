#include "Surface.h"

CSurface::CSurface(int columns, int rows, float xMin, float xMax, float yMin, float yMax)
	: m_rows(rows)
	, m_columns(columns)
	, m_xMin(xMin)
	, m_xMax(xMax)
	, m_yMin(yMin)
	, m_yMax(yMax)
	, m_displayList(0)
{
}

void CSurface::Draw()const
{
	// При первом обращении создаём дисплейны список (Дисплейный список представляет собой оптимизированное хранилище команд OpenGL, которое можно записать один раз и многократно вызывать без повторного вычисления команд.)
	if (m_displayList == 0)
	{
		m_displayList = glGenLists(1);
		glNewList(m_displayList, GL_COMPILE);

		// Вычисляем шаг узлов сетки
		const float dy = (m_yMax - m_yMin) / (m_rows - 1);
		const float dx = (m_xMax - m_xMin) / (m_columns - 1);

		float y = m_yMin;
		// Пробегаем по строкам сетки
		for (int row = 0; row < m_rows - 1; ++row, y += dy)
		{
			// Каждой строке будет соответствовать своя лента из треугольников
			// GL_TRIANGLES
			glBegin(GL_TRIANGLE_STRIP);
			float x = m_xMin;

			// Пробегаем по столбцам текущей строки
			for (int column = 0; column <= m_columns; ++column, x += dx)
			{
				// Вычисляем параметры вершины в узлах пары соседних вершин ленты из треугольников
				glm::vec3 v0 = { x, y + dy, 0 };
				glm::vec3 v1 = { x, y, 0 };

				// Координаты вершины на четной позиции
				glVertex3f(v0.x, v0.y, v0.z);
				// Координаты вершины на нечетной позиции
				glVertex3f(v1.x, v1.y, v1.z);
			}
			glEnd();
		}
		glEndList();
	}

	glCallList(m_displayList);
}

// Разрушаем дисплейный список в деструкторе
CSurface::~CSurface(void)
{
	if (m_displayList != 0)
	{
		glDeleteLists(m_displayList, 1);
	}
}