#pragma once
#pragma comment (lib, "glu32.lib")
#include "version.h"
#include "debug.h"
#ifdef BUILD_WINDOWS
	#include "../res/resource.h"
	#include <winuser.h>
	#include <tchar.h>
#endif
#include <gl/glu.h>
#include <GLFW/glfw3.h>
#include "graphics.h"
#include "controls.h"
#define WINDOW_SIZE 480
#define WINDOW_TITLE_REGULAR "Trails"
#define WINDOW_TITLE_FIRST_WIN "Blue wins!"
#define WINDOW_TITLE_SECOND_WIN "Red wins!"
extern GLFWwindow* window;
extern bool windowHere;
bool windowInit();
void windowSetup();
#ifdef BUILD_WINDOWS
void windowIcon(int resource);
#endif
void windowResize(GLFWwindow* window, int width, int height);
void windowUpdate(GLFWwindow* window);
void windowQuit(int code);
