#pragma once
#include "version.h"
#include <chrono>
#include <string>
#ifdef BUILD_WINDOWS
#define localtime(a, b) localtime_s(b, a)
#elif defined(BUILD_LINUX) || defined(BUILD_UNIX)
#define localtime(a, b) localtime_r(a, b)
#endif
#define PROGRAM_SUCCESS 0
#define PROGRAM_FAILURE -1
#define ERROR_GLFW_INIT "Failed to initialize GLFW library"
#define ERROR_GLFW_WINDOW "Failed to create GLFW window"
#define WARNING_WINDOW_SETUP "Window cannot be configured before initialization"
#define WARNING_FIELD_SIZE "Field size must be at least two, so it will be set to two"
#define WARNING_TOWERS_COUNT "Odd count of towers cannot be placed symmetrically when the field is even-sized, so count of towers will be increased by one"
#define TIMESTAMP_FORMAT "[. :]"
using namespace std;
using namespace chrono;
void error(const char* message);
void warning(const char* message);
string timestamp(const char format[6] = TIMESTAMP_FORMAT);
