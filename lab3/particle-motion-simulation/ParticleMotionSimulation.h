#pragma once
#include "BaseWindow.hpp"
#include "ParticleManager.h"

class ParticleMotionSimulation : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	// Глобальные переменные обработки добавления/удаления частиц
	ParticleManager m_particleManager;
	bool m_leftMouseButtonPressed = false;
	bool m_rightMouseButtonPressed = false;

	// Функция для обработки событий мыши
	void OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;

	// Функция для обработки нажатия на клавиши
	virtual void OnKeyButton(GLFWwindow* window, int key, int scancode, int action, int mods) override;

	void OnRunStart() override;
	void Draw(int width, int height) override;
};