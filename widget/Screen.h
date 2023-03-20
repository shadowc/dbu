#pragma once
#include "AbstractWidget.h"

class Screen : public AbstractWidget
{
public:
    Screen();
    virtual void OnResize();
    void SetLastCharPressed(char keyCode);

protected:
    void RenderWidget() override;
    char lastKeyCode;
};
