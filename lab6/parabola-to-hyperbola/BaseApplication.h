#pragma once

#include "inc.h"

class BaseApplication
{
public:
	void MainLoop();

protected:
	BaseApplication(
		char const* title,
		int width = 0,
		int height = 0,
		bool needDepth = true,
		bool needStencil = false);

	virtual void OnInit() {};
	virtual void OnDisplay() = 0;
	virtual void OnReshape(int width, int height);
	virtual void OnKeyboard(unsigned char key, int x, int y) {};
	virtual void OnMouse(int button, int state, int x, int y) {};
	virtual void OnMotion(int x, int y) {};
	virtual void OnIdle() {};

	void PostRedisplay();

private:
	void InitEventHandlers();

	static void DisplayHandler();
	static void ReshapeHandler(int width, int height);
	static void KeyboardHandler(unsigned char key, int x, int y);
	static void MouseHandler(int button, int state, int x, int y);
	static void MotionHandler(int x, int y);
	static void IdleHandler();

	static BaseApplication* m_application;
};