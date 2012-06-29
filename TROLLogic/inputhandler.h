#include <vector>
#include <GL/glfw.h>
#include <cassert>

//extern int _glfwInitialized;

struct InputHandler
{
	static bool isKeyDown(int key) 
	{ 
		//assert(_glfwInitialized && _glfwWin.opened); 
		assert(key <= GLFW_KEY_LAST);
		return glfwGetKey(key) == GLFW_PRESS; 
	}
	static void getMousePos(int *x, int *y) 
	{ 
		//assert(_glfwInitialized && _glfwWin.opened); 
		assert(x && y);
		glfwGetMousePos(x,y);
//		*x = _glfwInput.MousePosX;
//		*y = _glfwInput.MousePosY;
	}
};
