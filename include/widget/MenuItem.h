#pragma once

#include "AbstractWidget.h"
#include <string>

using namespace std;

class MenuItem : public AbstractWidget
{
public:
    void SetLabel(const string& newLabel);
    string GetLabel() const;
    bool IsSelected() const;
    void SetSelected(bool isSelected);

protected:
    string label;
    bool selected;

    void RenderWidget() override;
    void Invalidate() override;
};
