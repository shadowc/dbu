#pragma once
#include "AbstractWidget.h"
#include <functional>

class Menu : public AbstractWidget
{
public:
    void SetHorizontal();
    void SetVertical();

    bool IsHorizontal() const;
    bool IsVertical() const;

    void SetTopPadding(int padding);
    void SetSidePadding(int padding);

    void SetSelectedItem(int index);
    int GetSelectedItem();

    void OnEvent(Event& event) override;

    function<void()> onExitMenu = nullptr;

protected:
    void Invalidate() override;
    void RenderWidget() override;

    void HandleKeyPressedHorizontal(Event& event);
    void HandleKeyPressedVertical(Event& event);

    bool horizontal = true;
    int topPadding = 1;
    int sidePadding = 0;
};
