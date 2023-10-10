#include "Particle.h"
#include <cmath>

const float Particle::radius = 15.0f;
const float Particle::mass = 0.5f;
const float Particle::coulombConstant = 0.05f;
const float Particle::maxForce = 0.01f;
const float Particle::maxSpeed = 0.4f;

Particle::Particle(float x, float y, float charge)
	: m_x(x), m_y(y), m_charge(charge), m_vx(0.0f), m_vy(0.0f) {}

void Particle::Update() {
	m_x += m_vx;
	m_y += m_vy;

	float speed = std::sqrt(m_vx * m_vx + m_vy * m_vy);
	// Ограничение скорости
	if (speed > maxSpeed) {
		m_vx = maxSpeed * (m_vx / speed);
		m_vy = maxSpeed * (m_vy / speed);
	}
}

void Particle::Render() {
	glBegin(GL_TRIANGLE_FAN);
	if (m_charge > 0) {
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else {
		glColor3f(0.0f, 0.0f, 1.0f);
	}

	for (int i = 0; i <= 360; i += 10) {
		float angle = i * 3.14159265f / 180.0f;
		float xPos = m_x + radius * std::cos(angle);
		float yPos = m_y + radius * std::sin(angle);
		glVertex2f(xPos, yPos);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);

	const float padding = (Particle::radius / 2.0f) + 1;
	if (m_charge > 0) {
		// Cимвол "+"
		glVertex2f(m_x - padding, m_y);
		glVertex2f(m_x + padding, m_y);
		glVertex2f(m_x, m_y - padding);
		glVertex2f(m_x, m_y + padding);
	}
	else {
		// Cимвол "-"
		glVertex2f(m_x - padding, m_y);
		glVertex2f(m_x + padding, m_y);
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