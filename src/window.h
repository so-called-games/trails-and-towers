#pragma once
#include "version.h"
#include <GL/glu.h>
#include <GLFW/glfw3.h>
// Define window initial parameters.
#define WINDOW_DEFAULT_SIZE 480
#define WINDOW_MINIMAL_SIZE 160
#define WINDOW_TITLE_REGULAR "Trails and Towers"
// This titles are used when one of the players wins.
#define WINDOW_TITLE_FIRST_WIN "Blue wins"
#define WINDOW_TITLE_SECOND_WIN "Red wins"
extern GLFWwindow* window;
extern unsigned int screenWidth, screenHeight;
extern int windowWidth, windowHeight;
extern bool windowHere;
bool windowInit();
void windowSetup();
void windowSetTitle(const char* title);
// Icon change method (when program already runs) is defined only for Windows.
#ifdef BUILD_WINDOWS
void windowSetIcon(int resource);
#endif
void windowResize(GLFWwindow* window, int width, int height);
void windowUpdate(GLFWwindow* window);
void windowError(int, const char* message);
void windowQuit(int code);