#pragma once
#include "AbstractWidget.h"
#include <string>

class Dialog : public AbstractWidget
{
public:
    Dialog();

    void SetVisible(bool newVisible);
    void SetTitle(string newTitle);
    bool HasActiveMask() override;
    void Invalidate() override;
    void SetParent(AbstractWidget* widget) override;

protected:
    void RenderWidget() override;

private:
    bool visible;
    string title;
};
