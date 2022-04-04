#pragma comment (lib, "glu32.lib")
#include "window.h"
#include "debug.h"
#include "graphics.h"
#include "controls.h"
#ifdef BUILD_WINDOWS
#include "../res/resource.h"
#include <winuser.h>
#include <tchar.h>
#endif
GLFWwindow* window;
unsigned int screenWidth, screenHeight;
int windowWidth, windowHeight;
bool windowHere = false;
const int minWindowSize = 240;

bool windowInit()
{
	if (!glfwInit())
	{
		error(ERROR_GLFW_INIT);
		return false;
	}
	window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, WINDOW_TITLE_REGULAR, NULL, NULL);

	if (!window)
	{
		error(ERROR_GLFW_WINDOW);
		return false;
	}
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
	screenWidth = videoMode->width;
	screenHeight = videoMode->height;
	glfwMakeContextCurrent(window);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	return true;
}

void windowSetup()
{
	if (windowHere)
	{
		#ifdef BUILD_WINDOWS
			windowSetIcon(APP_ICON);
		#endif
		glfwSetWindowSizeLimits(window, minWindowSize, minWindowSize, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowRefreshCallback(window, windowUpdate);
		glfwSetWindowSizeCallback(window, windowResize);
		glfwSetKeyCallback(window, hitKey);
		glfwSetMouseButtonCallback(window, hitMouseButton);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void windowSetTitle(const char* title)
{
	glfwSetWindowTitle(window, title);
}

#ifdef BUILD_WINDOWS
	void windowSetIcon(int resource)
	{
		HWND hwnd = FindWindow(NULL, _T(WINDOW_TITLE_REGULAR));
		SIZE size = { GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON) };
		HICON hIcon = static_cast<HICON>(LoadImage(GetModuleHandleW(NULL), MAKEINTRESOURCE(resource), IMAGE_ICON, size.cx, size.cy, 0));
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
	}
#endif

void windowResize(GLFWwindow* window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	if (height == 0)
		height = 1;
	float sizeRatio = (float)width / height;
	cellResize((float)screenHeight / (width <= height ? width : height));
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width >= height)
		gluOrtho2D((-1.f - cellThickness) * sizeRatio, (1.f + cellThickness) * sizeRatio, -1.f - cellThickness, 1.f + cellThickness);
	else
		gluOrtho2D(-1.f - cellThickness, 1.f + cellThickness, (-1.f - cellThickness) / sizeRatio, (1.f + cellThickness) / sizeRatio);
	draw();
}

void windowUpdate(GLFWwindow* window)
{
	draw();
}

void windowQuit(int code = PROGRAM_SUCCESS)
{
	glfwTerminate();
	exit(code);
}
