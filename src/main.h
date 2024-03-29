﻿#pragma once
/* "version.h" header imports version and build definitions. Other headers might use it too if platform-specific code is being used.
 * Notice that this header is generated by CMake (see "version.h.in"), so it's not in the source code folder. */
#include "version.h"
// This is to hide console after startup on Windows (as the game is console application), unless build version isn't the debug one.
#if !defined(VERSION_DEBUG) && defined(BUILD_WINDOWS)
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif
#include "debug.h"
#include "window.h"
#include "graphics.h"
#include "logic.h"
#include <GLFW/glfw3.h>