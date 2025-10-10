#pragma once

#include "AbstractWidget.h"

class Menu : public AbstractWidget
{
public:
    void SetHorizontal();
    void SetVertical();

    bool IsHorizontal() const;
    bool IsVertical() const;

    void SetTopPadding(int padding);
    void SetSidePadding(int padding);

protected:
    void Invalidate() override;
    void RenderWidget() override;

    bool horizontal = true;
    int topPadding = 1;
    int sidePadding = 0;
};
