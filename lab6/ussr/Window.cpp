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

	/// <summary>
	/// probably, i should compute R based on center
	/// </summary>
	const char* vertexShaderSource = R"(
	#version 330 core

	layout (location = 0) in vec3 position;
	layout (location = 1) in vec2 aTexCoord;
	// uniform float aTime;
	// uniform float aC;
	// uniform float aA;
	//out vec3 ourColor;

	out vec2 TexCoord;

	uniform mat4 u_proj;
	uniform mat4 u_view;
	uniform mat4 u_model;
	
	void main()
	{	

		// gl_Position = u_proj * u_view * u_model * vec4(position.x, position.y,aA * position.z * sin(x - (aC * aTime)), 1.0); 

		gl_Position = u_proj * u_view * u_model * vec4(position, 1.0);
		TexCoord = aTexCoord;
	}
)";

	const char* fragmentShaderSource = R"(
	#version 330 core
	
	in vec2 TexCoord;

	out vec4 FragColor;

	uniform sampler2D texture1;

	void main()
	{
		FragColor = texture(texture1,TexCoord); 
	}
)";

	const char* geometryShaderSource = R"(
	#version 330 core
	layout (points) in;
	layout (triangle_strip, max_vertices = 5) out;

	//out vec3 fColor;

	void draw_point(vec4 position)
	{   
   
		//fColor = vec3(1.0, 0.0, 0.0);
		// gs_in[0] since there's only one input vertex
		gl_Position = position + vec4(-100, -100, 0.0, 0.0); // 1:bottom-left   
		EmitVertex();   
		gl_Position = position + vec4( 100, -100, 0.0, 0.0); // 2:bottom-right
		EmitVertex();
		gl_Position = position + vec4(-100,  100, 0.0, 0.0); // 3:top-left
		EmitVertex();
		gl_Position = position + vec4( 100,  100, 0.0, 0.0); // 4:top-right
		//fColor = vec3(1.0, 1.0, 1.0);

		EmitVertex();
		EndPrimitive();
	}

	void main() {    
		draw_point(gl_in[0].gl_Position);
	}
)";


	void CheckCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
	void CheckShaderLinkStatus(unsigned int ID) {
		int status;
		GLchar infoLog[1024];
		glGetProgramiv(ID, GL_LINK_STATUS, &status);
		if (!status) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << ID << "::LINKING_FAILURE\n" << infoLog << std::endl;
		}
		else {
			std::cout << "SHADER::" << ID << "::LINKING_SUCCESS" << std::endl;
		}
	}

	static const std::string
		UNIFORM_A = "aA",
		UNIFORM_C = "aC",
		UNIFORM_TIME = "aTime",
		UNIFORM_CAMERA_POS = "u_cameraPos";

	glm::mat4 rotateOver(const glm::mat4& model, const glm::vec3& point, const float angle, const glm::vec3 axis) {
		auto translationMatrix = glm::translate(glm::mat4(1.0f), -point);
		auto rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
		return glm::inverse(translationMatrix) * rotationMatrix * translationMatrix * model;
	}

} // namespace



Window::Window(int w, int h, const char* title)
	: IBaseWindow(w, h, title)

{
	m_physicsWorld = std::make_shared<b2World>(b2Vec2(0.f, 0.f));

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
	m_colisionCircle = m_physicsWorld->CreateBody(&bodyDef);
	m_colisionCircle->CreateFixture(&fixtureDef);
	m_colisionCircle->SetFixedRotation(true);


}


void Window::OnMouseButton(int button, int action, int mods)
{
	/*if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_leftButtonPressed = (action & GLFW_PRESS) != 0;
	}*/
}

void Window::OnMouseMove(double x, double y)
{
	//const glm::dvec2 mousePos{ x, y };
	//if (m_leftButtonPressed)
	//{
	//	const auto windowSize = GetFramebufferSize();

	//	const auto mouseDelta = mousePos - m_mousePos;
	//	const double xAngle = mouseDelta.y * M_PI / windowSize.y;
	//	const double yAngle = mouseDelta.x * M_PI / windowSize.x;
	//	RotateCamera(xAngle, yAngle);
	//}
	//m_mousePos = mousePos;
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
		{Shader::ShaderType::VERTEX_SHADER, "D:\\projects\\cdlabs\\lb6\\SSSR\\SSSR\\vertex.vert"},
		{Shader::ShaderType::FRAGMENT_SHADER, "D:\\projects\\cdlabs\\lb6\\SSSR\\SSSR\\fragment.frag"},
		});
	auto time = glfwGetTime();


	m_appliedTexture.Setup("D:\\projects\\cdlabs\\lb6\\SSSR\\SSSR\\Flag_of_the_Soviet_Union.svg.png");
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

	modelMatrix = glm::translate(modelMatrix, glm::vec3(-100, -130, 0));


	//modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime()*0.01f, glm::vec3(1, 0, 0));
	//modelMatrix = rotateOver(modelMatrix, flagPos,-(float)glfwGetTime() * 0.03f, glm::vec3(0,1, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-30, 0, 10));

	//flagPos = modelMatrix * glm::vec4( flagPos, 1.0f);


	m_shader.UniformMatrix4f(
		modelMatrix,
		"u_model"
	);
	m_shader.UniformFloat(4, UNIFORM_A);
	m_shader.UniformFloat(8, UNIFORM_C);
	m_shader.UniformFloat(glfwGetTime(), UNIFORM_TIME);
	m_shader.UniformVec3f(m_cameraPos, UNIFORM_CAMERA_POS);
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
	//m_cameraMatrix = glm::lookAt(m_position, m_position + m_directtion, m_up);
}

void Window::RotateCamera(float amount, const glm::vec3& axis)
{
	//m_directtion = glm::vec3(glm::rotate(glm::vec4(m_directtion, 1.0f), amount * m_angleSpeed, axis));
}

void Window::TranslateCamera(const glm::vec3& deriction)
{
	//m_position += deriction;
}

void Window::MoveCamera(const glm::vec3& deriction)
{
	//m_position = deriction;
}