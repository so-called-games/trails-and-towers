#pragma once
#include "version.h"
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#define WINDOW_DEFAULT_SIZE 480
#define WINDOW_MINIMAL_SIZE 160
#define WINDOW_TITLE_REGULAR "Trails and Towers"
#define WINDOW_TITLE_FIRST_WIN "Blue wins"
#define WINDOW_TITLE_SECOND_WIN "Red wins"
extern GLFWwindow* window;
extern unsigned int screenWidth, screenHeight;
extern int windowWidth, windowHeight;
extern bool windowHere;
bool windowInit();
void windowSetup();
void windowSetTitle(const char* title);
#ifdef BUILD_WINDOWS
void windowSetIcon(int resource);
#endif
void windowResize(GLFWwindow* window, int width, int height);
void windowUpdate(GLFWwindow* window);
void windowQuit(int code);