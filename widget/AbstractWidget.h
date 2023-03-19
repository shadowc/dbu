#pragma once
#include "../console/ConsoleTools.h"
#include <vector>

using namespace Console;
using namespace std;

class AbstractWidget {
public:
    AbstractWidget();
    ~AbstractWidget();

    void Draw();

    Coords GetPosition();
    void SetPosition(Coords newCoords);
    void SetPosition(int x, int y);
    Size GetSize();
    void SetSize(Size newSize);
    void SetSize(int w, int h);
    void Invalidate();

protected:
    bool invalidated;
    Coords coords;
    Size size;
    vector<AbstractWidget*> Children;

    virtual void Initialize();
    virtual void RenderWidget();
    virtual void TearDown();
};
