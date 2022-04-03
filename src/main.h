#pragma once
#if !defined(VERSION_DEBUG) && defined(BUILD_WINDOWS)
	#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif
#include "debug.h"
#include "window.h"
#include "graphics.h"
#include "logic.h"
#include <GLFW/glfw3.h>
