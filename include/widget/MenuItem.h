#pragma once

#include "AbstractWidget.h"
#include <string>
#include <functional>

using namespace std;

class MenuItem : public AbstractWidget
{
public:
    void SetLabel(const string& newLabel);
    string GetLabel() const;
    bool IsSelected() const;
    void SetSelected(bool isSelected);
    void Execute();
    void SetAction(function<void()> func);

protected:
    string label;
    bool selected;
    function<void()> action;

    void RenderWidget() override;
    void Invalidate() override;
};
