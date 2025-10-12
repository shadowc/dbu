#pragma once
#include "MenuEntry.h"
#include <vector>

class MenuConfig
{
public:
    MenuConfig();
    void RenderMenu();

private:
    vector<MenuEntry> entries;
    vector<int> selectedItems;

    bool initialized;
};
