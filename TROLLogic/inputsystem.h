#pragma once
#include <TROLUtil/error.h>
#include <vector>
#include "iinputhandler.h"

#ifdef TROL_USE_OLD_OPENGL
	#include <GL/glew.h>
#else
	#include <GL3/gl3w.h>
#endif

#include <GL/glfw.h>


struct InputSystem
{
	bool isKeyDown(int key);
	void getMousePos(int *x, int *y);
	void getMousePos(float *x, float *y);
	void centerMouse();
    void registerKeyHandler(IKeyInputHandler* h) { keyHandlers.push_back(h); }
    void registerMouseHandler(IMouseInputHandler* h) { mouseHandlers.push_back(h); }

    static void GLFWCALL keyCallback(int key, int action);

    void update();

private:
    static InputSystem* isystem;
	friend class Root;
    TROLLOERROR init();
	void destroy() {}
    std::vector<IKeyInputHandler*> keyHandlers;
    std::vector<IMouseInputHandler*> mouseHandlers;
};
