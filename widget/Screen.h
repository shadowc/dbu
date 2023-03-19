#pragma once
#include "AbstractWidget.h"

class Screen : public AbstractWidget
{
public:
    virtual void OnResize();

protected:
    void Initialize() override;
    void RenderWidget() override;    
};
