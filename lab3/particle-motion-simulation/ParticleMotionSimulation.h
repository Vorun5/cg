#pragma once
#include "BaseWindow.hpp"
#include "ParticleManager.h"

class ParticleMotionSimulation : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	// ���������� ���������� ��������� ����������/�������� ������
	ParticleManager m_particleManager;
	bool m_leftMouseButtonPressed = false;
	bool m_rightMouseButtonPressed = false;

	// ������� ��� ��������� ������� ����
	void OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;

	// ������� ��� ��������� ������� �� �������
	virtual void OnKeyButton(GLFWwindow* window, int key, int scancode, int action, int mods) override;

	void OnRunStart() override;
	void Draw(int width, int height) override;
};