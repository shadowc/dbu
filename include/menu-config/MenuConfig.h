#pragma once
#include "MenuEntry.h"
#include <vector>

class Menu;

class MenuConfig
{
public:
    MenuConfig();
    void RenderMenu();

    void ActivateMenu();
    void ActivateSubMenu(int index);
    void DeactivateSubMenu();

private:
    vector<MenuEntry> entries;
    vector<Menu*> activeMenus;
    vector<int> openSubMenuIndexes;

    bool initialized;
};
