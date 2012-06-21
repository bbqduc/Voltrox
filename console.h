#pragma once

#define MAXROWSIZE 256
#define BACKLOGROWS 64

class Console
{
public:
	void handleInput();
private:
	char* backlog[BACKLOGROWS][MAXROWSIZE];
	uint8_t cursorPosition; // Position on current row
	
};
