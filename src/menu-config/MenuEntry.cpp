#include "menu-config/MenuEntry.h"
#include <string>
#include <functional>

using namespace std;

MenuEntry::MenuEntry(string label, function<void()> action)
{
    this->label = label;
    this->action = action;
}

void MenuEntry::AddEntry(const MenuEntry& entry)
{
    subEntries.push_back(entry);
}
