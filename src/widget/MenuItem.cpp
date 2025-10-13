#include "widget/Menu.h"
#include "Application.h"
#include "widget/MenuItem.h"
#include "console/Console.h"
#include <string>
#include <iostream>
#include <functional>

using namespace std;
using namespace Console;

void MenuItem::SetLabel(const string& text)
{
    label = text;
    Invalidate();
}

string MenuItem::GetLabel() const
{
    return label;
}

bool MenuItem::IsSelected() const
{
    return selected;
}

void MenuItem::SetSelected(bool isSelected)
{
    selected = isSelected;
    Invalidate();
}

void MenuItem::Execute()
{
    if (action) {
        action();
    }
}

void MenuItem::SetAction(function<void()> action)
{
    this->action = action;
}

void MenuItem::RenderWidget()
{
    ConsoleTty* console = Application::GetConsole();
    ColorScheme scheme = console->getColorScheme();

    console->setColor(selected ? scheme.MenuSelected : scheme.Menu);
    console->FillLine(coords.Y, coords.X, coords.X + size.Width, ' ');
    console->setPos(coords.X, coords.Y);
    cout << label;
}

void MenuItem::Invalidate()
{
    AbstractWidget::Invalidate();

    Menu* menuParent = dynamic_cast<Menu*>(parent);

    if (menuParent == nullptr) {
        coords.X = 1;
        coords.Y = 1;
        size.Width = label.length();
        size.Height = 1;
        return;
    }

    Coords parentCoords = parent->GetPosition();
    Size parentSize = parent->GetSize();

    int itemIndex = 0;

    for (int n = 0; n < menuParent->GetChildLength(); n++) {
        AbstractWidget* child = menuParent->GetChildAt(n);

        if (child->GetUniqueId() == this->GetUniqueId()) {
            itemIndex = n;
            break;
        }
    }

    size.Height = 1; // fixed height for menu item
    
    if (menuParent->IsHorizontal()) {
        coords.Y = parentCoords.Y;
        size.Width = label.length();

        MenuItem* previousItem = itemIndex > 0 ? dynamic_cast<MenuItem*>(menuParent->GetChildAt(itemIndex - 1)) : nullptr;
        if (previousItem == nullptr) {
            coords.X = 1;
        } else {
            coords.X = previousItem->coords.X + previousItem->size.Width;
        }
    } else {
        coords.X = parentCoords.X + (menuParent->HasBorder() ? 1 : 0);
        coords.Y = parentCoords.Y + itemIndex + (menuParent->HasBorder() ? 1 : 0);
        size.Width = parentSize.Width - (menuParent->HasBorder() ? 2 : 0);
    }
}
