#pragma once

#include "AbstractWidget.h"
#include "event/EventDef.h"
#include "menu-config/MenuConfig.h"
#include <string>

class Menu;

class Screen : public AbstractWidget
{
public:
    Screen();
    void OnResize() override;
    void SetLastCharPressed(int keyCode);
    bool HasActiveMask() override;
    void OnEvent(Event& event) override;

protected:
    void RenderWidget() override;
    int lastKeyCode;
    string platformName;
    string versionMajor;
    string versionMinor;
    MenuConfig menuConfig;

    Menu* FindMenu();
};
