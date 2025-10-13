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
    void ActivateSubMenu();
    void DeactivateSubMenu();

private:
    vector<MenuEntry> entries;
    vector<Menu*> activeMenus;

    vector<MenuEntry> FindNextSubEntries();

    bool initialized;
};
