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
    void CycleMenuRight();
    void CycleMenuLeft();

private:
    vector<MenuEntry> entries;
    vector<Menu*> activeMenus;

    vector<MenuEntry> FindNextSubEntries();

    bool initialized;
};
