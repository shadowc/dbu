#pragma once

#include <vector>
#include <string>

using namespace std;
class AbstractAction;

class MenuEntry
{
public:
    MenuEntry(string label, AbstractAction* action = nullptr);
    ~MenuEntry();

    void AddEntry(const MenuEntry& entry);

    string label;
    AbstractAction *action = nullptr;
    vector<MenuEntry> subEntries;
};
