#include "AbstractWidget.h"
#include <vector>

using namespace std;

AbstractWidget::AbstractWidget() {
    size = Size(10, 1);
    coords = Coords(1, 1);
    invalidated = true;
    Children = vector<AbstractWidget*>();

    Initialize();
}

AbstractWidget::~AbstractWidget() {
    TearDown();
}

void AbstractWidget::Draw() {
    if (invalidated) {
        RenderWidget();

        for (AbstractWidget* child : Children) {
            child->Draw();
        }

        invalidated = false;
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
    invalidated = false;

    for (AbstractWidget* child : Children) {
        child->Invalidate();
    }
}

void AbstractWidget::OnResize() {}

void AbstractWidget::Initialize() {}

void AbstractWidget::RenderWidget() {}

void AbstractWidget::TearDown() {
    for (AbstractWidget* child : Children) {
        child->TearDown();
    }

    Children.clear();
}
