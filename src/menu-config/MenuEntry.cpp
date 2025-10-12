#include "menu-config/MenuEntry.h"
#include "menu-config/actions/AbstractAction.h"
#include <string>

using namespace std;

MenuEntry::MenuEntry(string label, AbstractAction* action)
{
    this->label = label;
    this->action = action;
}

MenuEntry::~MenuEntry()
{
    if (action != nullptr) {
        delete action;
        action = nullptr;
    }
}

void MenuEntry::AddEntry(const MenuEntry& entry)
{
    subEntries.push_back(entry);
}
