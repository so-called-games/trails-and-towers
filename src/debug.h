#pragma once
#include "version.h"
#include <chrono>
#include <string>
#include <iostream>
#ifdef BUILD_WINDOWS
	#define localtime(a, b) localtime_s(b, a)
#elif defined(BUILD_LINUX) || defined(BUILD_UNIX)
	#define localtime(a, b) localtime_r(a, b)
#endif
#define PROGRAM_SUCCESS 0
#define PROGRAM_FAILURE -1
#define ERROR_GLFW_INIT "Failed to initialize GLFW library"
#define ERROR_GLFW_WINDOW "Failed to create GLFW window"
#define ERROR_SDL_INIT "Failed to initialize SDL library"
#define ERROR_AUDIO_DEVICE "Failed to open audio device"
#define TIMESTAMP_FORMAT "[. :]"
using namespace std;
using namespace chrono;
void error(const char* message);
void warning(const char* message);
string timestamp(const char format[6] = TIMESTAMP_FORMAT);
