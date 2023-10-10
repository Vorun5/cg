#pragma once
#include <vector>
#include "Particle.h"

class ParticleManager {
public:
    ParticleManager();

    void AddParticle(float x, float y, float charge);
    bool RemoveParticle(float x, float y);
    void RemoveAllParticles();
    void UpdateAllParticles(int width, int height);
    void RenderAllParticles();

private:
    std::vector<Particle> particles;
};
