
#include <GLFW/glfw3.h>
#include <stdexcept>

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title)
		: m_window{ MakeWindow(w, h, title) }
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}

		glfwSetWindowUserPointer(m_window, this);


		glfwSetMouseButtonCallback(m_window,
			[](GLFWwindow* window, int button, int action, int mods) {
				GetBaseWindow(window)->OnMouseButton(window, button, action, mods);
			});

		glfwSetCursorPosCallback(m_window,
			[](GLFWwindow* window, double x, double y) {
				GetBaseWindow(window)->OnMouseMove(window, x, y);
			});

		glfwSetKeyCallback(m_window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods) {
				GetBaseWindow(window)->OnKeyButton(window, key, scancode, action, mods);
			});
	}

	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow() {
		glfwDestroyWindow(m_window);
	}


	void Run() {
		glfwMakeContextCurrent(m_window);
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		// ��������� ��������� ������� ����
		glfwSetWindowSizeLimits(m_window, width, height, width, height);
		// ��������� ��������� ����� ��������� (��� � html, css)
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		// ��������� ������ ����
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		OnRunStart();

		while (!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			int w, h;
			glfwGetFramebufferSize(m_window, &w, &h);
			
			Draw(w, h);

			glFinish();
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
		OnRunEnd();
	};

private:
	static BaseWindow* GetBaseWindow(GLFWwindow* window) {
		return reinterpret_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
	};

	virtual void OnMouseButton(
		[[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int button, [[maybe_unused]] int action,
		[[maybe_unused]] int mods) {}
	virtual void OnMouseMove(
		[[maybe_unused]] GLFWwindow* window, [[maybe_unused]] double x, [[maybe_unused]] double y) {}
	virtual void OnKeyButton(
		[[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int key, [[maybe_unused]] int scancode, [[maybe_unused]] int action, [[maybe_unused]] int mods) {}
	virtual void Draw(int width, int height) = 0;
	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* MakeWindow(int w, int h, const char* title)
	{
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		return glfwCreateWindow(w, h, title, nullptr, nullptr);
	};

	GLFWwindow* m_window;
};


