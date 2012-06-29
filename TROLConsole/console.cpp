#include "console.h"

void Console::handleKeyEvent(int key, int action)
{
	if(action == GLFW_PRESS)
	{
		if(isascii(key)) 
			backlog[0].insert(cursorPosition++, 1, (char) key);
		else if(key == GLFW_KEY_BACKSPACE && cursorPosition > 0)
			backlog[0].erase(--cursorPosition,1);
		else if(key == GLFW_KEY_DEL)
			backlog[0].erase(cursorPosition,1);
		else if(key == GLFW_KEY_LEFT)
			cursorPosition = cursorPosition ? cursorPosition-1 : cursorPosition;
		else if(key == GLFW_KEY_RIGHT)
			cursorPosition = cursorPosition+1 == backlog[0].length() ? cursorPosition+1 : cursorPosition;
		else if(key == GLFW_KEY_ENTER)
		{
			performCommand(backlog[0].c_str());
			cursorPosition = 0;
			backlog[0].clear(); // TODO : shift backlog
		}
	}
}
