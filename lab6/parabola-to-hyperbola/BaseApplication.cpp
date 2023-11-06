#include "BaseApplication.h"

BaseApplication* BaseApplication::m_application = nullptr;

void BaseApplication::MainLoop()
{
	OnInit();
	glutMainLoop();
}

BaseApplication::BaseApplication(char const* title, int width, int height, bool needDepth, bool needStencil)
{
	if (m_application)
	{
		throw std::runtime_error("Only one instance of application is permitted");
	}
	m_application = this;

	int argc = 1;
	char const* argv[] = { "" };
	glutInit(&argc, const_cast<char**>(argv));

	glutInitDisplayMode(
		GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE | (needDepth ? GLUT_DEPTH : 0) | (needStencil ? GLUT_STENCIL : 0));

	if (width > 0 && height > 0)
	{
		glutInitWindowSize(width, height);
	}

	glutCreateWindow(title);

	InitEventHandlers();
}

void BaseApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void BaseApplication::PostRedisplay()
{
	glutPostRedisplay();
}

void BaseApplication::InitEventHandlers()
{
	glutDisplayFunc(&DisplayHandler);
	glutReshapeFunc(&ReshapeHandler);
	glutKeyboardFunc(&KeyboardHandler);
	glutMouseFunc(&MouseHandler);
	glutMotionFunc(&MotionHandler);
	glutIdleFunc(&IdleHandler);
}

void BaseApplication::DisplayHandler()
{
	m_application->OnDisplay();
	glutSwapBuffers();
}

void BaseApplication::ReshapeHandler(int width, int height)
{
	m_application->OnReshape(width, height);
}

void BaseApplication::KeyboardHandler(unsigned char key, int x, int y)
{
	m_application->OnKeyboard(key, x, y);
}

void BaseApplication::MouseHandler(int button, int state, int x, int y)
{
	m_application->OnMouse(button, state, x, y);
}

void BaseApplication::MotionHandler(int x, int y)
{
	m_application->OnMotion(x, y);
}

void BaseApplication::IdleHandler()
{
	m_application->OnIdle();
}