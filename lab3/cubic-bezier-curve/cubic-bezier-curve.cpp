
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <vector>

class GLFWInitializer final
{
public:
	GLFWInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	GLFWInitializer(const GLFWInitializer&) = delete;
	GLFWInitializer& operator=(const GLFWInitializer&) = delete;

	~GLFWInitializer()
	{
		glfwTerminate();
	}
};


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
	}

	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow() {
		glfwDestroyWindow(m_window);
	}


	void Run() {
		glfwMakeContextCurrent(m_window);
		// ��������� ��������� ������� ����
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
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


class CubicBezierCurve : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:
	// ���������� ���������� ��� �������� ����� ������ �����
	std::vector<glm::vec2> m_controlPoints;
	const int M_NUM_SEGMENTS = 100;

	// ���������� ��� ���������� ������������ �����
	int m_selectedPointIndex = -1;
	glm::vec2 m_offset;
	bool m_isDragging = false;

	// ������� ��� ���������� ������������� ������������ C(n, k)
	float CalculateBinomialCoefficient(int n, int k) {
		int numerator = 1;
		int denominator = 1;
		for (int i = 0; i < k; i++) {
			numerator *= (n - i);
			denominator *= (i + 1);
		}
		return static_cast<float>(numerator) / static_cast<float>(denominator);
	}

	// ������� ��� ���������� ����� �� ������ �����
	glm::vec2 CalculateBezierPoint(float t) {
		int n = m_controlPoints.size() - 1;
		glm::vec2 point(0.0f, 0.0f);
		for (int i = 0; i <= n; i++) {
			float binomialCoefficient = CalculateBinomialCoefficient(n, i);
			float term1 = pow(1.0f - t, n - i);
			float term2 = pow(t, i);
			point += binomialCoefficient * term1 * term2 * m_controlPoints[i];
		}
		return point;
	}

	// ������� ��� ��������� ���������� ����� ����� �������
	void DrawDashedLines() {
		glLineStipple(1, 0xAAAA); // ������������� ���������� ����� �����
		glEnable(GL_LINE_STIPPLE);

		glColor3f(0.0f, 0.0f, 0.0f); // ������������� ������ ���� �����
		glLineWidth(1.0f); // ������������� ������� �����

		glBegin(GL_LINES);
		for (int i = 0; i < m_controlPoints.size() - 1; i++) {
			glVertex2f(m_controlPoints[i].x, m_controlPoints[i].y);
			glVertex2f(m_controlPoints[i + 1].x, m_controlPoints[i + 1].y);
		}
		glEnd();

		glDisable(GL_LINE_STIPPLE); // ��������� ���������� �����
	}

	// ������� ��� ��������� ������� ����
	void OnMouseButton(GLFWwindow* window, int button, int action, int mods) override {
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (action == GLFW_PRESS) {
			for (int i = 0; i < m_controlPoints.size(); i++) {
				if (glm::length(glm::vec2(mouseX, mouseY) - m_controlPoints[i]) < 10.0f) {
					m_selectedPointIndex = i;
					m_offset = glm::vec2(mouseX, mouseY) - m_controlPoints[i];
					m_isDragging = true;
					break;
				}
			}
		}
		else if (action == GLFW_RELEASE) {
			m_selectedPointIndex = -1;
			m_isDragging = false;
		}
	}

	// ������� ��� ��������� ����������� ����
	void OnMouseMove(GLFWwindow* window, double xpos, double ypos) override {
		if (m_isDragging) {
			m_controlPoints[m_selectedPointIndex] = glm::vec2(xpos, ypos) - m_offset;
		}
	}

	void OnRunStart() override {
		// ��������� ��������� ����������� �����
		m_controlPoints.push_back(glm::vec2(100.0f, 300.0f));
		m_controlPoints.push_back(glm::vec2(200.0f, 500.0f));
		m_controlPoints.push_back(glm::vec2(600.0f, 100.0f));
		m_controlPoints.push_back(glm::vec2(700.0f, 300.0f));
	}

	void Draw(int width, int height) override
	{
		glColor3f(1.0f, 0.0f, 0.0f); // ������������� ������� ���� �����
		glLineWidth(3.0f); // ������������� ������� �����

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= M_NUM_SEGMENTS; i++) {
			float t = static_cast<float>(i) / static_cast<float>(M_NUM_SEGMENTS);
			glm::vec2 point = CalculateBezierPoint(t);
			glVertex2f(point.x, point.y);
		}
		glEnd();

		// ������ ����������� �����
		glColor3f(0.0f, 0.0f, 1.0f); // ������������� ����� ���� ��� ����������� �����
		glPointSize(14.0f); // ������������� ������ �����
		glBegin(GL_POINTS);

		for (int i = 0; i < m_controlPoints.size(); i++) {
			if (i == m_selectedPointIndex) {
				glColor3f(1.0f, 0.0f, 0.0f); // ������������� ������� ���� ��� ��������� �����
			}
			glVertex2f(m_controlPoints[i].x, m_controlPoints[i].y);
			if (i == m_selectedPointIndex) {
				glColor3f(0.0f, 0.0f, 1.0f); // ���������� ����� ���� ��� ��������� �����
			}
		}
		glEnd();

		// ������ ���������� ����� ����� �������
		DrawDashedLines();
	}
};

int main()
{
	GLFWInitializer initGLFW;
	CubicBezierCurve bizier{ 800, 600, "Cubic Bezier Curve" };
	bizier.Run();
	return 0;
}
