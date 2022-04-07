#pragma once
#include "version.h"
#include <chrono>
#include <string>
// Arguments in following function must be swapped as it's different on a different platforms.
#ifdef BUILD_WINDOWS
#define localtime(a, b) localtime_s(b, a)
#elif defined(BUILD_LINUX) || defined(BUILD_UNIX)
#define localtime(a, b) localtime_r(a, b)
#endif
// Define program exit codes.
#define PROGRAM_SUCCESS 0
#define PROGRAM_FAILURE -1
// Define errors and warning messages.
#define ERROR_GLFW_INIT "Failed to initialize GLFW library"
#define ERROR_GLFW_WINDOW "Failed to create GLFW window"
#define WARNING_WINDOW_SETUP "Window cannot be configured before initialization"
#define WARNING_FIELD_SIZE "Field size must be at least two, so it will be set to two"
#define WARNING_TOWERS_COUNT "Odd count of towers cannot be placed symmetrically when the field is even-sized, so count of towers will be increased by one"
// Define date and time separators for error and warning timestamps in debug console.
#define TIMESTAMP_FORMAT "[. :]"
using namespace std;
using namespace chrono;
void error(const char* message);
void warning(const char* message);
// If timestamp format was not provided, use defined ones.
string timestamp(const char format[6] = TIMESTAMP_FORMAT);