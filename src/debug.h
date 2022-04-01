#pragma once
#include "version.h"
#include <iostream>
#include <string>
#include <chrono>
#ifdef BUILD_WINDOWS
	#define localtime(a, b) localtime_s(b, a)
#elif defined(BUILD_LINUX) || defined(BUILD_UNIX)
	#define localtime(a, b) localtime_r(a, b)
#endif
#define PROGRAM_SUCCESS 0
#define PROGRAM_FAILURE -1
#define ERROR_GLFW_INIT "Failed to initialize GLFW library"
#define ERROR_GLFW_WINDOW "Failed to create GLFW window"
#define TIMESTAMP_FORMAT "[. :]"
using namespace std;
using namespace chrono;
void error(const char* message);
void warning(const char* message);
string timestamp(const char format[6] = TIMESTAMP_FORMAT);
