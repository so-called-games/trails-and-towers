/********************************************************************************
 * Trails and Towers - http://trails.sogamestudios.com
 * Cross-platform mathematical game
 * ------------------------------------------------------------------------------
 * Copyright (c) 2022 So. Game Studios
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ********************************************************************************/

/* This game doesn't provide configuration or network playing features (which were considered at some point) to remain simple.
 * It is important to source code to be easily understandable, so only GLFW library is being used for the game.
 * This file includes entry points for the game. */
#include "main.h"

int main(int argc, char* argv[])
{
	/* Initialize graphics and logic of the game.
	 * Notice that "windowQuit" method immideatly terminates the game in case of error. */
	if (!(windowHere = windowInit()))
		windowQuit(PROGRAM_FAILURE);
	windowSetup();
	fieldInit();
	drawInit();

	// If everything is OK, let player do some actions.
	while (!glfwWindowShouldClose(window))
	{
		// As the game doesn't use any animation between players turns, it renders only after ones.
		glfwPollEvents();
	}
	windowQuit(PROGRAM_SUCCESS);
}