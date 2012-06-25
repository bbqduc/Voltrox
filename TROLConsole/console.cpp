#include "console.h"

void Console::handleKeyEvent(int key, int action)
{
	if(action == GLFW_PRESS)
	{
		if(isascii(key)) 
		{
			memmove(&backlog[0][cursorPosition+1], &backlog[0][cursorPosition], MAXROWSIZE - cursorPosition);
			backlog[0][cursorPosition] = key;
			cursorPosition = cursorPosition == MAXROWSIZE-1 ? cursorPosition : cursorPosition + 1;
		}
		else if(key == GLFW_KEY_BACKSPACE && cursorPosition > 0)
		{
			--cursorPosition;
			memmove(&backlog[0][cursorPosition], &backlog[0][cursorPosition+1], MAXROWSIZE - cursorPosition);
		}
		else if(key == GLFW_KEY_DEL)
			memmove(&backlog[0][cursorPosition], &backlog[0][cursorPosition+1], MAXROWSIZE - cursorPosition);
		else if(key == GLFW_KEY_LEFT)
			cursorPosition = cursorPosition ? cursorPosition-1 : cursorPosition;
		else if(key == GLFW_KEY_RIGHT)
			cursorPosition = cursorPosition+1 == currentCmdLength ? cursorPosition : cursorPosition+1;
		else if(key == GLFW_KEY_ENTER)
		{
			performCommand(backlog[0]);
			memmove(backlog[1], backlog[0], MAXROWSIZE * BACKLOGROWS);
			memset(backlog[0], 0, MAXROWSIZE);
		}
	}
}
