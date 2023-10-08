#include "ParticleManager.h"
#include <cmath>

ParticleManager::ParticleManager() {
	particles.reserve(25); // ����������� ����� ��� 25 ������
}

void ParticleManager::addParticle(float x, float y, float charge) {
	particles.emplace_back(x, y, charge);
}

bool ParticleManager::removeParticle(float x, float y) {
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		// ���������, ���� ���������� ������� ������ � ��������� �����������
		float dx = it->GetX() - x;
		float dy = it->GetY() - y;
		float distanceSquared = dx * dx + dy * dy;
		if (distanceSquared < Particle::radius * Particle::radius) {
			// ������� ������� �� �������
			particles.erase(it);
			return true; // ������� �� ����� ����� ��������
		}
	}
	return false;
}

void ParticleManager::removeAllParticles() {
	particles.clear();
}

void ParticleManager::updateAllParticles(int width, int height) {
	for (auto& particle : particles) {
		// ���������� ������� �������
		particle.Update();

		// ��������, �������� �� ������� ������ ����
		float particleX = particle.GetX();
		float particleY = particle.GetY();

		if (particleX - Particle::radius < 0 || particleX + Particle::radius > width) {
			// ������� �������� ����� ��� ������ ������� ����, �������� vx �� ��������������� ��������
			particle.SetVelocity(-particle.GetVx(), particle.GetVy());
		}

		if (particleY - Particle::radius < 0 || particleY + Particle::radius > height) {
			// ������� �������� ������� ��� ������ ������� ����, �������� vy �� ��������������� ��������
			particle.SetVelocity(particle.GetVx(), -particle.GetVy());
		}

		// ���������� � ���������� ���� ������ ����� ���������
		for (auto& otherParticle : particles) {
			if (&particle == &otherParticle) {
				continue; // ���������� ��������� ������� � ����� �����
			}

			float dx = otherParticle.GetX() - particle.GetX();
			float dy = otherParticle.GetY() - particle.GetY();
			float distanceSquared = dx * dx + dy * dy;
			float distance = std::sqrt(distanceSquared);

			// ��������� ���� ������
			float forceMagnitude = Particle::coulombConstant * particle.GetCharge() * (-1 * otherParticle.GetCharge()) / distanceSquared;

			if (forceMagnitude > Particle::maxForce) {
				forceMagnitude = Particle::maxForce;
			}

			// ��������� ������ ����
			float forceX = forceMagnitude * (dx / distance);
			float forceY = forceMagnitude * (dy / distance);

			// ��������� ���� � �������
			particle.AddVelocity(forceX / Particle::mass, forceY / Particle::mass);
		}
	}
}

void ParticleManager::renderAllParticles() {
	for (auto& particle : particles) {
		particle.Render();
	}
}
