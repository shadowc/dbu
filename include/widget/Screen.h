#pragma once

#include "AbstractWidget.h"
#include <string>

class Screen : public AbstractWidget
{
public:
    Screen();
    virtual void OnResize();
    void SetLastCharPressed(char keyCode);

protected:
    void RenderWidget() override;
    int lastKeyCode;
    string platformName;
    string versionMajor;
    string versionMinor;
};
