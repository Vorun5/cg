#include "ParticleMotionSimulation.h"

void ParticleMotionSimulation::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			m_leftMouseButtonPressed = true;
			if (m_particleManager.removeParticle(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
				return;
			}
			m_particleManager.addParticle(static_cast<float>(mouseX), static_cast<float>(mouseY), 1.0f);
		}
		else if (action == GLFW_RELEASE) {
			m_leftMouseButtonPressed = false;
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			m_rightMouseButtonPressed = true;
			if (m_particleManager.removeParticle(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
				return;
			}
			m_particleManager.addParticle(static_cast<float>(mouseX), static_cast<float>(mouseY), -1.0f);
		}
		else if (action == GLFW_RELEASE) {
			m_rightMouseButtonPressed = false;
		}
	}
}

void ParticleMotionSimulation::OnKeyButton(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
		m_particleManager.removeAllParticles();
	}
}

void ParticleMotionSimulation::OnRunStart()
{
}

void ParticleMotionSimulation::Draw(int width, int height)
{
	m_particleManager.updateAllParticles(width, height);
	m_particleManager.renderAllParticles();
}
