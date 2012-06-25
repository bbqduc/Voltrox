#pragma once

#define BACKLOGROWS 4

#include <ctype.h> // int isascii(int c)
#include <cstring>
#include <GL/glfw.h>
#include <stdint.h>
#include <iostream>
#include <string>

class Console
{
	public:
		void handleKeyEvent(int key, int action);
		const char* getCurrentText() { return backlog[0].c_str(); }
		std::string backlog[BACKLOGROWS];
		Console():cursorPosition(0) {}

	private:
		int cursorPosition; // Position on current row
		void performCommand(const char* c) { std::cout << "PERFORMED COMMAND : " << c << '\n'; }
};

