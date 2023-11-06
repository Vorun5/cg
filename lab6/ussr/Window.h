#pragma once
#include "Shaider.h"
#include "Texture2D.h"
#include "BaseWindow.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Scene.h"

class Window : public BaseWindow
{

public:
	Window(int w, int h, const char* title);

private:

	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;

	void OnMouseMove(double x, double y) override;

	void OnKeyButton(int key, int scancode, int action, int mods) override;

	void RotateCamera(double xAngleRadians, double yAngleRadians);

	void OnResize(int width, int height) override;

	void OnRunStart() override;
	void Draw(int width, int height) override;
	void SetupCameraMatrix();
	void UpdateCamera();
	void RotateCamera(float amount, const glm::vec3& axis);
	void TranslateCamera(const glm::vec3& deriction);
	void MoveCamera(const glm::vec3& deriction);


	static constexpr double DISTANCE_TO_ORIGIN = 100;

	float m_speed = 1.1f;
	float m_angleSpeed = 0.1f;


	bool m_leftButtonPressed = false;
	float m_colisionRadius = 2;
	/*Shader m_shader;*/
	GLuint m_texture, m_shaderProgram;
	Scene m_scene;

	glm::dmat4 m_perspectoveMatrix;
	glm::dvec2 m_mousePos = {};
	glm::dvec3 m_distance{ 0.0, 0.0, DISTANCE_TO_ORIGIN },
		m_position{ 0.0, 0.0, 0.0 },
		m_up{ 0.0, 1.0, 0.0 },
		m_directtion{ 0.0, 0.0, DISTANCE_TO_ORIGIN };

	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		m_distance,
		m_position,
		m_up);
	glm::vec3 m_cameraPos = ([=]() { auto m = glm::inverse(m_cameraMatrix); return m[3]; })();
	Texture2D m_appliedTexture;
	Shader m_shader;
};