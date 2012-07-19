#pragma once
#include <TROLUtil/error.h>
#include <vector>

struct IKeyInputHandler
{
    virtual void handleKeyEvent(int key, int action) = 0;
};

struct IMouseInputHandler
{
    virtual void handleMousePos(float x, float y) = 0;
    virtual void handleMouseClick(int button, int action) = 0;
};


struct InputSystem
{
	bool isKeyDown(int key);
	void getMousePos(int *x, int *y);
	void getMousePos(float *x, float *y);
	void centerMouse();

private:
	friend class Root;
	TROLLOERROR init() {return TROLLO_OK;}
	void destroy() {}
    std::vector<IKeyInputHandler*> keyHandlers;
    std::vector<IMouseInputHandler*> mouseHandlers;
};
