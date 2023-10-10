#include "ParticleManager.h"
#include <cmath>

ParticleManager::ParticleManager() {
	particles.emplace_back(300.0f, 315.0f, -1.0f);
	particles.emplace_back(300.0f, 300.0f, 1.0f);

	particles.emplace_back(100.0f, 315.0f, -1.0f);
	particles.emplace_back(300.0f, 100.0f, 1.0f);

	particles.emplace_back(150.0f, 100.0f, -1.0f);
	particles.emplace_back(300.0f, 150.0f, 1.0f);

	particles.emplace_back(500.0f, 300.0f, -1.0f);
	particles.emplace_back(500.0f, 350.0f, 1.0f);

	particles.emplace_back(600.0f, 550.0f, -1.0f);
	particles.emplace_back(600.0f, 500.0f, 1.0f);

	particles.emplace_back(200.0f, 550.0f, -1.0f);
	particles.emplace_back(200.0f, 500.0f, 1.0f);

	particles.emplace_back(100.0f, 500.0f, -1.0f);
	particles.emplace_back(100.0f, 550.0f, 1.0f);

	particles.emplace_back(444.0f, 222.0f, -1.0f);
	particles.emplace_back(555.0f, 222.0f, 1.0f);

	particles.emplace_back(333.0f, 333.0f, -1.0f);
	particles.emplace_back(222.0f, 222.0f, 1.0f);

	particles.emplace_back(50.0f, 111.0f, -1.0f);
	particles.emplace_back(20.0f, 111.0f, 1.0f);
}

void ParticleManager::AddParticle(float x, float y, float charge) {
	particles.emplace_back(x, y, charge);
}

bool ParticleManager::RemoveParticle(float x, float y) {
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		float dx = it->GetX() - x;
		float dy = it->GetY() - y;
		float distanceSquared = dx * dx + dy * dy;
		if (distanceSquared < Particle::radius * Particle::radius) {
			particles.erase(it);
			return true; 
		}
	}
	return false;
}

void ParticleManager::RemoveAllParticles() {
	particles.clear();
}

void ParticleManager::UpdateAllParticles(int width, int height) {
	const float minSeparationDistance = 31.0f; 
	const float dampingFactor = 0.999f;

	for (auto& particle : particles) {
		particle.Update();

		// Проверка, достигла ли частица границ окна
		float particleX = particle.GetX();
		float particleY = particle.GetY();

		// Частица достигла левой или правой границы окна
		if (particleX - Particle::radius < 0 || particleX + Particle::radius > width) {
			particle.SetVelocity(-particle.GetVx(), particle.GetVy());
		}

		// Частица достигла верхней или нижней границы окна
		if (particleY - Particle::radius < 0 || particleY + Particle::radius > height) {
			particle.SetVelocity(particle.GetVx(), -particle.GetVy());
		}

		particle.SetVelocity(particle.GetVx() * dampingFactor, particle.GetVy() * dampingFactor);

		// Вычисление и применение силы Кулона между частицами
		for (auto& otherParticle : particles) {
			if (&particle == &otherParticle) {
				continue;
			}

			float dx = otherParticle.GetX() - particle.GetX();
			float dy = otherParticle.GetY() - particle.GetY();
			float distanceSquared = dx * dx + dy * dy;
			float distance = std::sqrt(distanceSquared);

			if (distanceSquared < minSeparationDistance * minSeparationDistance) {
				// Если частицы слишком близко, вычисляем вектор отталкивания и применяем его
				float distance = std::sqrt(distanceSquared);
				float overlap = minSeparationDistance - distance;
				float separationX = (overlap / distance) * dx;
				float separationY = (overlap / distance) * dy;

				// Рассчитываем скорости после столкновения
				float particleVx = particle.GetVx();
				float particleVy = particle.GetVy();
				float otherParticleVx = otherParticle.GetVx();
				float otherParticleVy = otherParticle.GetVy();
				float totalMass = Particle::mass + Particle::mass;

				float newParticleVx = (Particle::mass - Particle::mass) / totalMass * particleVx +
					(2.0f * Particle::mass) / totalMass * otherParticleVx;
				float newParticleVy = (Particle::mass - Particle::mass) / totalMass * particleVy +
					(2.0f * Particle::mass) / totalMass * otherParticleVy;

				float newOtherParticleVx = (2.0f * Particle::mass) / totalMass * particleVx +
					(Particle::mass - Particle::mass) / totalMass * otherParticleVx;
				float newOtherParticleVy = (2.0f * Particle::mass) / totalMass * particleVy +
					(Particle::mass - Particle::mass) / totalMass * otherParticleVy;

				particle.SetVelocity(newParticleVx, newParticleVy);
				otherParticle.SetVelocity(newOtherParticleVx, newOtherParticleVy);

				// Применяем отталкивающую силу к частицам
				particle.AddVelocity(-separationX / Particle::mass, -separationY / Particle::mass);
				otherParticle.AddVelocity(separationX / Particle::mass, separationY / Particle::mass);
			}
			else {
				// Вычисляем силу Кулона только если частицы находятся достаточно далеко друг от друга
				float forceMagnitude = Particle::coulombConstant * particle.GetCharge() * (-1 * otherParticle.GetCharge()) / distanceSquared;

				if (forceMagnitude > Particle::maxForce) {
					forceMagnitude = Particle::maxForce;
				}

				// Вычисляем вектор силы
				float forceX = forceMagnitude * (dx / distance);
				float forceY = forceMagnitude * (dy / distance);

				// Применяем силу к частице
				particle.AddVelocity(forceX / Particle::mass, forceY / Particle::mass);
			}
		}
	}
}

void ParticleManager::RenderAllParticles() {
	for (auto& particle : particles) {
		particle.Render();
	}
}
