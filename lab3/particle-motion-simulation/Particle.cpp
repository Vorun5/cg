#include "Particle.h"
#include <cmath>

const float Particle::radius = 15.0f;
const float Particle::mass = 1.0f;
const float Particle::coulombConstant = 0.02f;
const float Particle::maxForce = 0.01f;
const float Particle::maxSpeed = 0.9f;

Particle::Particle(float x, float y, float charge)
	: m_x(x), m_y(y), m_charge(charge), m_vx(0.0f), m_vy(0.0f) {}

void Particle::Update() {
	// Обновление позиции частицы с учетом скорости
	m_x += m_vx;
	m_y += m_vy;

	float speed = std::sqrt(m_vx * m_vx + m_vy * m_vy);
	// Ограничение скорости, чтобы избежать слишком быстрого движения
	if (speed > maxSpeed) {
		m_vx = maxSpeed * (m_vx / speed);
		m_vy = maxSpeed * (m_vy / speed);
	}
}

void Particle::Render() {
	// Отрисовка частицы как круга с цветом в зависимости от заряда
	glBegin(GL_TRIANGLE_FAN);
	if (m_charge > 0) {
		glColor3f(1.0f, 0.0f, 0.0f); // Красный для положительной частицы
	}
	else {
		glColor3f(0.0f, 0.0f, 1.0f); // Синий для отрицательной частицы
	}

	for (int i = 0; i <= 360; i += 10) {
		float angle = i * 3.14159265f / 180.0f;
		float xPos = m_x + radius * std::cos(angle);
		float yPos = m_y + radius * std::sin(angle);
		glVertex2f(xPos, yPos);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f); // Устанавливаем черный цвет
	glLineWidth(3.0f);
	glBegin(GL_LINES);

	if (m_charge > 0) {
		// Рисуем символ "+"
		glVertex2f(m_x - 8.0f, m_y);
		glVertex2f(m_x + 8.0f, m_y);
		glVertex2f(m_x, m_y - 8.0f);
		glVertex2f(m_x, m_y + 8.0f);
	}
	else {
		// Рисуем символ "-"
		glVertex2f(m_x - 8.0f, m_y);
		glVertex2f(m_x + 8.0f, m_y);
	}
	glEnd();
}

void Particle::SetVelocity(float newVx, float newVy) {
	m_vx = newVx;
	m_vy = newVy;
}

void Particle::AddVelocity(float deltaVx, float deltaVy) {
	m_vx += deltaVx;
	m_vy += deltaVy;
}

float Particle::GetX() const {
	return m_x;
}

float Particle::GetY() const {
	return m_y;
}

float Particle::GetVx() const {
	return m_vx;
}

float Particle::GetVy() const {
	return m_vy;
}

float Particle::GetCharge() const {
	return m_charge;
}