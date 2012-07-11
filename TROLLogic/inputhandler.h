#pragma once
#include <TROLUtil/error.h>

struct InputHandler
{
	bool isKeyDown(int key);
	void getMousePos(int *x, int *y);
	void getMousePos(float *x, float *y);
	void centerMouse();

private:
	friend class Root;
	TROLLOERROR init() {return TROLLO_OK;}
	void destroy() {}
};
