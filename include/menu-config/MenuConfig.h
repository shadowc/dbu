#pragma once
#include "MenuEntry.h"
#include "console/ConsoleTools.h"
#include <vector>

using namespace Console;
class Menu;

class MenuConfig
{
public:
    MenuConfig();
    void RenderMenu();

    void ActivateMenu();
    void DeactivateMenu();
    void ActivateSubMenu();
    void DeactivateSubMenu();
    void CycleMenuRight();
    void CycleMenuLeft();

private:
    vector<MenuEntry> entries;
    vector<Menu*> activeMenus;

    vector<MenuEntry> FindNextSubEntries();
    Coords GetPositionForSubMenu(Menu* parentMenu, int selectedIndex);

    bool initialized;
};
