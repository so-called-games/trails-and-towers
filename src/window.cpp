#include "window.h"
GLFWwindow* window;
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
	glfwMakeContextCurrent(window);
	return true;
}

void windowSetup()
{
	if (windowHere)
	{
		#ifdef BUILD_WINDOWS
			windowIcon(APP_ICON);
		#endif
		glfwSetWindowSizeLimits(window, minWindowSize, minWindowSize, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowRefreshCallback(window, windowUpdate);
		glfwSetWindowSizeCallback(window, windowResize);
		glfwSetKeyCallback(window, hitKey);
		glfwSetMouseButtonCallback(window, hitMouseButton);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

#ifdef BUILD_WINDOWS
	void windowIcon(int resource)
	{
		HWND hwnd = FindWindow(NULL, _T(WINDOW_TITLE_REGULAR));
		SIZE size = { GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON) };
		HICON hIcon = static_cast<HICON>(LoadImage(GetModuleHandleW(NULL), MAKEINTRESOURCE(resource), IMAGE_ICON, size.cx, size.cy, 0));
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
	}
#endif

void windowResize(GLFWwindow* window, int width, int height)
{
	if (height == 0)
		height = 1;
	float ratio = (float)width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width >= height)
		gluOrtho2D((-1.f - cellThickness) * ratio, (1.f + cellThickness) * ratio, -1.f - cellThickness, 1.f + cellThickness);
	else
		gluOrtho2D(-1.f - cellThickness, 1.f + cellThickness, (-1.f - cellThickness) / ratio, (1.f + cellThickness) / ratio);
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
