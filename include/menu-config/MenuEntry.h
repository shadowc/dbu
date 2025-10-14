#pragma once
#include <vector>
#include <string>
#include <functional>

using namespace std;

class MenuEntry
{
public:
    MenuEntry(string label, function<void()> action = nullptr, function<bool()> isEnabledCallback = nullptr);

    void AddEntry(const MenuEntry& entry);

    string label;
    function<void()> action = nullptr;
    function<bool()> isEnabledCallback = nullptr;
    vector<MenuEntry> subEntries;
};
