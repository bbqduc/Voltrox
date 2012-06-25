#pragma once

#define MAXROWSIZE 256
#define BACKLOGROWS 64

#include <ctype.h> // int isascii(int c)
#include <cstring>
#include <GLFW/glfw.h>

class Console
{
	public:
		void handleKeyEvent(int key, int action);
	private:
		char* backlog[BACKLOGROWS][MAXROWSIZE];
		uint8_t cursorPosition; // Position on current row
		uint8_t currentCmdLength;
		void performCommand(const char* c) { std::cout << "PERFORMED COMMAND : " << c << '\n'; }
};

