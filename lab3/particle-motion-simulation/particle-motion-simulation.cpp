#include "ParticleManager.h"
#include "GLFWInitializer.hpp"
#include "ParticleMotionSimulation.h"

int main() {
	GLFWInitializer initGLFW;
	ParticleMotionSimulation simulation{ 800, 600, "Particle Motion Simulation", 60.0 };
	simulation.Run();
	return 0;
}
