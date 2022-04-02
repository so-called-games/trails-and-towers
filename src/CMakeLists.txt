set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
option(VERSION_DEBUG "Defines if version of the game is debug" OFF)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(VERSION_DEBUG ON)
endif()
configure_file("version.h.in" "version.h")
add_executable (${PROJECT_NAME}
	main.cpp
	debug.cpp
	window.cpp
	graphics.cpp
	audio.cpp
	controls.cpp
	settings.cpp
	logic.cpp)

if (WIN32)
	target_sources(${PROJECT_NAME} PRIVATE
	"${PROJECT_SOURCE_DIR}/res/resource.h"
	"${PROJECT_SOURCE_DIR}/res/icon.rc")
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
target_link_libraries (${PROJECT_NAME} glfw)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2-static)
