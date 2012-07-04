#pragma once

struct InputHandler
{
	bool isKeyDown(int key);
	void getMousePos(int *x, int *y);
	void getMousePos(float *x, float *y);
	void centerMouse();

private:
	friend class Root;
	void init() {}
	void destroy() {}
};
