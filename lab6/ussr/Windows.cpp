#include "pch.h"
#include "Window.h"
#include "DirectLight.h"
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

namespace
{
	constexpr double FIELD_OF_VIEW = 60 * M_PI / 180.0;
	constexpr double CUBE_SIZE = 1;

	constexpr double Z_NEAR = 0.1;
	constexpr double Z_FAR = 100;

	glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m)
	{
		const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
		return {
			glm::dvec4{ normalizedMatrix[0], 0.0 },
			glm::dvec4{ normalizedMatrix[1], 0.0 },
			glm::dvec4{ normalizedMatrix[2], 0.0 },
			m[3]
		};
	}

	static const std::string
		UNIFORM_A = "aA",
		UNIFORM_C = "aC",
		UNIFORM_TIME = "aTime",
		UNIFORM_CAMERA_POS = "u_cameraPos";

	// Поворачивает модельную матрицу вокруг определённой точки
	glm::mat4 rotateOver(const glm::mat4& model, const glm::vec3& point, const float angle, const glm::vec3 axis) {
		auto translationMatrix = glm::translate(glm::mat4(1.0f), -point);
		auto rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
		return glm::inverse(translationMatrix) * rotationMatrix * translationMatrix * model;
	}
} // namespace



Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)

{
	b2BodyDef bodyDef;
	auto pos = b2Vec2(m_position.x, m_position.z);
	bodyDef.position = pos;
	bodyDef.type = b2_dynamicBody;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;

	b2CircleShape circleShape;
	circleShape.m_p = b2Vec2(0, 0)/*pos*/;
	circleShape.m_radius = .5f;
	fixtureDef.shape = &circleShape;
}


void Window::OnMouseButton(int button, int action, int mods)
{
}

void Window::OnMouseMove(double x, double y)
{
}

void Window::OnKeyButton(int key, int scancode, int action, int mods)
{
}


void Window::RotateCamera(double xAngleRadians, double yAngleRadians)
{
	const glm::dvec3 xAxis{
		m_cameraMatrix[0][0], m_cameraMatrix[1][0], m_cameraMatrix[2][0]
	};
	const glm::dvec3 yAxis{
		m_cameraMatrix[0][1], m_cameraMatrix[1][1], m_cameraMatrix[2][1]
	};
	m_cameraMatrix = glm::rotate(m_cameraMatrix, xAngleRadians, xAxis);
	m_cameraMatrix = glm::rotate(m_cameraMatrix, yAngleRadians, yAxis);

	m_cameraMatrix = Orthonormalize(m_cameraMatrix);
}

void Window::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	m_perspectoveMatrix = glm::perspective(FIELD_OF_VIEW, aspect, Z_NEAR, Z_FAR);
	glLoadMatrixd(&m_perspectoveMatrix[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void Window::OnRunStart()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	DirectLight light1{ m_position };
	light1.SetDiffuseIntensity({ 0.5f, 0.5f, 0.5f, 1.0f });
	light1.SetAmbientIntensity({ 0.2f, 0.2f, 0.2f, 1.0f });
	light1.SetSpecularIntensity({ 0.3f, 0.3f, 0.3f, 1.0f });
	light1.SetSpotDirection(m_directtion);
	light1.Apply(GL_LIGHT1);
	m_shader.Setup({
		{Shader::ShaderType::VERTEX_SHADER, "vertex.vert"},
		{Shader::ShaderType::FRAGMENT_SHADER, "fragment.frag"},
		});
	auto time = glfwGetTime();


	m_appliedTexture.Setup("ussr.png");
	m_scene.SetupFlag(m_appliedTexture.GetHeight(), m_appliedTexture.GetWidth());
}

void Window::Draw(int width, int height)
{
	glViewport(0, 0, width, height);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraMatrix();
	glColor4f(1, 1, 1, 1);
	glUseProgram(m_shaderProgram);
	m_shader.Use();
	m_shader.UniformMatrix4f(glm::mat4(m_perspectoveMatrix), "u_proj");
	m_shader.UniformMatrix4f(glm::mat4(m_cameraMatrix), "u_view");
	auto modelMatrix = glm::mat4(1.0f);
	auto flagPos = m_scene.GetFlagPos();
	modelMatrix = rotateOver(modelMatrix, flagPos, glm::radians(270.f), glm::vec3(0, 0, 1));


	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f / 4.f, 1.f / 4.f, 1.f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-200, -230, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-30, 0, 10));

	m_shader.UniformMatrix4f(
		modelMatrix,
		"u_model"
	);
	m_shader.UniformFloat(4, UNIFORM_A);
	m_shader.UniformFloat(8, UNIFORM_C);
	m_shader.UniformFloat(glfwGetTime(), UNIFORM_TIME);
	m_shader.UniformVec3f(m_cameraPos, UNIFORM_CAMERA_POS);
	// Активируем текстуру и передаём её в frag texture1
	m_appliedTexture.activate();
	m_scene.Draw();
}

void Window::SetupCameraMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&m_cameraMatrix[0][0]);
}

void Window::UpdateCamera()
{
}

void Window::RotateCamera(float amount, const glm::vec3& axis)
{
}

void Window::TranslateCamera(const glm::vec3& deriction)
{
}

void Window::MoveCamera(const glm::vec3& deriction)
{
}