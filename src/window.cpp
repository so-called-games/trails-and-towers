// This file includes window operation methods.
#include "window.h"
#include "debug.h"
#include "graphics.h"
#include "controls.h"
// <iostream> is needed to output GLFW errors.
#include <iostream>
// Import resource and some other headers to change game icon on Windows.
#ifdef BUILD_WINDOWS
#include "../res/resource.h"
#include <winuser.h>
#include <tchar.h>
#endif
using namespace std;
GLFWwindow* window;
// Screen height is being used to calculate adaptive grid thickness.
unsigned int screenWidth, screenHeight;
int windowWidth, windowHeight;
// This variable is used by some methods to check if window was initialized.
bool windowHere = false;

bool windowInit()
{
	glfwSetErrorCallback(windowError);

	// If some error occured, the game will terminate.
	if (!glfwInit())
	{
		error(ERROR_GLFW_INIT);
		return false;
	}
	window = glfwCreateWindow(WINDOW_DEFAULT_SIZE, WINDOW_DEFAULT_SIZE, WINDOW_TITLE_REGULAR, NULL, NULL);

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
	// Window must be initialized to that moment.
	if (windowHere)
	{
		#ifdef BUILD_WINDOWS
			windowSetIcon(APP_ICON);
		#endif
		glfwSetWindowSizeLimits(window, WINDOW_MINIMAL_SIZE, WINDOW_MINIMAL_SIZE, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowRefreshCallback(window, windowUpdate);
		glfwSetWindowSizeCallback(window, windowResize);
		glfwSetKeyCallback(window, hitKey);
		glfwSetMouseButtonCallback(window, hitMouseButton);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
		warning(WARNING_WINDOW_SETUP);
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
	// Change cell size and grid thickness based on window size.
	cellResize((float)screenHeight / (width <= height ? width : height));
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// This is to remain proportions of the field. It will add extra space outside of the field when window size ratio isn't equal to 1.
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

void windowError(int, const char* message)
{
	cerr << timestamp() << "GLFW error: " << message << endl;
}

void windowQuit(int code)
{
	glfwTerminate();
	exit(code);
}