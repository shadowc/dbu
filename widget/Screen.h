#pragma once
#include "AbstractWidget.h"

class Screen : public AbstractWidget
{
public:
    Screen();
    virtual void OnResize();

protected:
    void RenderWidget() override;    
};
