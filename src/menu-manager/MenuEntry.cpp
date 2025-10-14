#include "menu-manager/MenuEntry.h"
#include <string>
#include <functional>

using namespace std;

MenuEntry::MenuEntry(string label, function<void()> action, function<bool()> isEnabledCallback)
{
    this->label = label;
    this->action = action;
    this->isEnabledCallback = isEnabledCallback;
}

void MenuEntry::AddEntry(const MenuEntry& entry)
{
    subEntries.push_back(entry);
}
