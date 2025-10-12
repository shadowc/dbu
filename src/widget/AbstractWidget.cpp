#include "widget/AbstractWidget.h"
#include "Application.h"
#include "console/Console.h"
#include "console/ConsoleTools.h"
#include "event/EventQueue.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace Console;

unsigned int AbstractWidget::nextElementId = 0;

unsigned int AbstractWidget::generateId()
{
    return AbstractWidget::nextElementId++;
}

AbstractWidget::AbstractWidget() {
    uniqueId = generateId();
    size = Size(10, 1);
    coords = Coords(1, 1);
    invalidated = true;
    children = vector<AbstractWidget*>();
    parent = nullptr;
    colorScheme = "default";
}

AbstractWidget::~AbstractWidget() {
    TearDown();
}

void AbstractWidget::Draw() {
    ConsoleTty* console = Application::GetConsole();

    if (invalidated) {
        for (AbstractWidget* child : children) {
            if (child->HasActiveMask()) {
                console->AddMask(child->GetActiveMask());
            }
        }

        console->colorSchemeManager->setColorScheme(GetColorScheme());
        RenderWidget();
        console->clearMasks();
        
        invalidated = false;
    }

    for (AbstractWidget* child : children) {
        child->Draw();
    }

    // Flush the console output if this is the top-level widget
    if (parent == nullptr) {
        console->Flush();
    }
}

Coords AbstractWidget::GetPosition() {
    return coords;
}

void AbstractWidget::SetPosition(Coords newCoords) {
    coords.X = newCoords.X;
    coords.Y = newCoords.Y;
    Invalidate();
}

void AbstractWidget::SetPosition(int x, int y) {
    coords.X = x;
    coords.Y = y;
    Invalidate();
}

Size AbstractWidget::GetSize() {
    return size;
}

void AbstractWidget::SetSize(Size newSize) {
    size.Width = newSize.Width;
    size.Height = newSize.Height;
    Invalidate();
}

void AbstractWidget::SetSize(int w, int h) {
    size.Width = w;
    size.Height = h;
    Invalidate();
}

void AbstractWidget::Invalidate() {
    invalidated = true;

    for (AbstractWidget* child : children) {
        child->Invalidate();
    }
}

void AbstractWidget::OnResize() {}

void AbstractWidget::RenderWidget() {}

void AbstractWidget::TearDown() {
    for (AbstractWidget* child : children) {
        child->TearDown();
    }

    children.clear();
}

AbstractWidget* AbstractWidget::GetParent()
{
    return parent;
}

void AbstractWidget::AddChild(AbstractWidget* child)
{
    if (child != nullptr) {
        children.push_back(child);
        child->SetParent(this);
        Invalidate();
    }
}

unsigned int AbstractWidget::GetUniqueId()
{
    return uniqueId;
}

bool AbstractWidget::HasFocus()
{
    return hasFocus;
}

void AbstractWidget::Focus()
{
    hasFocus = true;

    Application::GetEventQueue()->SetCurrentFocusedWidget(this);
}

void AbstractWidget::Blur()
{
    hasFocus = false;

    Application::GetEventQueue()->SetCurrentFocusedWidget(nullptr);
}

int AbstractWidget::GetChildLength()
{
    return (int)children.size();
}

AbstractWidget* AbstractWidget::GetChildAt(int index)
{
    return children[index];
}

void AbstractWidget::SetParent(AbstractWidget* newParent)
{
    // Remove from old parent if we have one
    if (parent != nullptr) {
        for (int n = 0; n < parent->GetChildLength(); n++) {
            if (parent->GetChildAt(n)->GetUniqueId() == uniqueId) {
                parent->RemoveChildAt(n);
                break;
            }
        }
    }

    parent = newParent;
    colorScheme = parent->GetColorScheme();

    // Add to new parent if we aren't added yet
    if (parent != nullptr) {
        bool found = false;

        for (int n = 0; n < parent->GetChildLength(); n++) {
            if (parent->GetChildAt(n)->GetUniqueId() == uniqueId) {
                found = true;
                break;
            }
        }

        if (!found) {
            parent->AddChild(this);
        }
    }

    Invalidate();
}

void AbstractWidget::RemoveParent()
{
    parent = nullptr;
}


void AbstractWidget::RemoveChild(AbstractWidget* child)
{
    auto it = children.begin();

    for (unsigned int n = 0; n < children.size(); n++) {
        auto currentChild = children[n];

        if (currentChild->GetUniqueId() == child->GetUniqueId()) {
            
            children[n]->RemoveParent();
            children.erase(it + n);

            Invalidate();

            break;
        }
    }
}

void AbstractWidget::RemoveChildAt(int position)
{
    if (position >= children.size()) {
        throw runtime_error("Invalid position for element children");
    }

    auto it = children.begin();

    children[position]->RemoveParent();
    children.erase(it + position);

    Invalidate();
}

bool AbstractWidget::HasActiveMask()
{
    return true;
}

Mask AbstractWidget::GetActiveMask()
{
    return Mask(coords.X, coords.Y, size.Width, size.Height);
}

void AbstractWidget::SetColorScheme(string newColorScheme)
{
    colorScheme = newColorScheme;

    for (AbstractWidget* child : children) {
        child->SetColorScheme(newColorScheme);
    }

    invalidated = true;
}

string AbstractWidget::GetColorScheme()
{
    return colorScheme;
}

void AbstractWidget::OnEvent(Event& event)
{
    // Base implementation does nothing
}
