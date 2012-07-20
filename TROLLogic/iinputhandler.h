#pragma once

struct IKeyInputHandler
{
    virtual void handleKeyEvent(int key, int action) = 0;
    virtual void update() = 0;
};

struct IMouseInputHandler
{
    virtual void handleMouseMove(float x, float y) = 0;
    virtual void handleMouseClick(int button, int action) = 0;
};
