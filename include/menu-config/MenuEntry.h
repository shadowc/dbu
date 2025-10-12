#pragma once
#include <vector>
#include <string>
#include <functional>

using namespace std;

class MenuEntry
{
public:
    MenuEntry(string label, function<void()> action = nullptr);

    void AddEntry(const MenuEntry& entry);

    string label;
    function<void()> action = nullptr;
    vector<MenuEntry> subEntries;
};
