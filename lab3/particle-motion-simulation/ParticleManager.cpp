#include "ParticleManager.h"
#include <cmath>

ParticleManager::ParticleManager() {
	particles.reserve(25); // –езервируем место дл€ 25 частиц
}

void ParticleManager::addParticle(float x, float y, float charge) {
	particles.emplace_back(x, y, charge);
}

bool ParticleManager::removeParticle(float x, float y) {
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		// ѕровер€ем, если координаты частицы близки к указанным координатам
		float dx = it->GetX() - x;
		float dy = it->GetY() - y;
		float distanceSquared = dx * dx + dy * dy;
		if (distanceSquared < Particle::radius * Particle::radius) {
			// ”дал€ем частицу из вектора
			particles.erase(it);
			return true; // ¬ыходим из цикла после удалени€
		}
	}
	return false;
}

void ParticleManager::removeAllParticles() {
	particles.clear();
}

void ParticleManager::updateAllParticles(int width, int height) {
	for (auto& particle : particles) {
		// ќбновление позиции частицы
		particle.Update();

		// ѕроверка, достигла ли частица границ окна
		float particleX = particle.GetX();
		float particleY = particle.GetY();

		if (particleX - Particle::radius < 0 || particleX + Particle::radius > width) {
			// „астица достигла левой или правой границы окна, измен€ем vx на противоположное значение
			particle.SetVelocity(-particle.GetVx(), particle.GetVy());
		}

		if (particleY - Particle::radius < 0 || particleY + Particle::radius > height) {
			// „астица достигла верхней или нижней границы окна, измен€ем vy на противоположное значение
			particle.SetVelocity(particle.GetVx(), -particle.GetVy());
		}

		// ¬ычисление и применение силы  улона между частицами
		for (auto& otherParticle : particles) {
			if (&particle == &otherParticle) {
				continue; // ѕропускаем сравнение частицы с самой собой
			}

			float dx = otherParticle.GetX() - particle.GetX();
			float dy = otherParticle.GetY() - particle.GetY();
			float distanceSquared = dx * dx + dy * dy;
			float distance = std::sqrt(distanceSquared);

			// ¬ычисл€ем силу  улона
			float forceMagnitude = Particle::coulombConstant * particle.GetCharge() * (-1 * otherParticle.GetCharge()) / distanceSquared;

			if (forceMagnitude > Particle::maxForce) {
				forceMagnitude = Particle::maxForce;
			}

			// ¬ычисл€ем вектор силы
			float forceX = forceMagnitude * (dx / distance);
			float forceY = forceMagnitude * (dy / distance);

			// ѕримен€ем силу к частице
			particle.AddVelocity(forceX / Particle::mass, forceY / Particle::mass);
		}
	}
}

void ParticleManager::renderAllParticles() {
	for (auto& particle : particles) {
		particle.Render();
	}
}
