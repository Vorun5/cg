#pragma once
#include <vector>
#include "Particle.h"

class ParticleManager {
public:
    ParticleManager();

    void addParticle(float x, float y, float charge);
    bool removeParticle(float x, float y);
    void removeAllParticles();
    void updateAllParticles(int width, int height);
    void renderAllParticles();

private:
    std::vector<Particle> particles;
};
