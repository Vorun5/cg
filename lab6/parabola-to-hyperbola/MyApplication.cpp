#include "MyApplication.h"
#include "ShaderLoader.h"

DWORD g_lastTick = GetTickCount();

CMyApplication::CMyApplication(char const* title, Size windowSize)
	: BaseApplication(title, windowSize.width, windowSize.height),
	m_windowSize(windowSize),
	m_surface(25, 25, -0.5, 0.5, -0.5, 0.5)
{
}

void CMyApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1, 1, 1, 1);

	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(
		2, 2, -1,  // Позиция камеры
		0, 0, 0,   // Точка, на которую камера смотрит
		1, 1, 0    // Вектор, указывающий направление "вверх"
	);
	
	InitShaders();
}

void CMyApplication::OnDisplay()
{
	DWORD currentTick = (DWORD)GetTickCount64();
	float timeInSeconds = (currentTick - g_lastTick) / 1000.0f;
	g_lastTick = currentTick;

	// С -1 до 3 - up
	// С 3 до 0 - !up
	static float workTime = 0;
	static bool up = true;
	if (up) {
		workTime += timeInSeconds;
		if (workTime >= 3)
		{
			up = false;
		}
	}
	if (!up) {
		workTime -= timeInSeconds;
		if (workTime < 0)
		{
			up = true;
		}
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glUseProgram(m_program);

	GLint timeUniform = glGetUniformLocation(m_program, "u_time");
	glUniform1f(timeUniform, workTime);

	m_surface.Draw();

	glUseProgram(0);
	glPopMatrix();

	PostRedisplay();
}

void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, aspect, 1, 30);
	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::InitShaders()
{
	ShaderLoader loader;
	Shader vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "TransformationVertex.glsl");
	Shader fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "TransformationFragment.glsl");

	vertexShader.Compile();
	fragmentShader.Compile();

	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	m_program.Link();
}