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
    virtual void OnResize();

    AbstractWidget* GetParent();
    void SetParent(AbstractWidget*);
    void RemoveParent();
    void AddChild(AbstractWidget* child);
    void RemoveChild(AbstractWidget* child);
    void RemoveChildAt(int index);
    int GetChildLength();
    AbstractWidget* GetChildAt(int index);

    virtual bool HasActiveMask();
    Mask GetActiveMask();

    unsigned int GetUniqueId();
protected:
    unsigned int uniqueId;
    bool invalidated;
    Coords coords;
    Size size;
    vector<AbstractWidget*> children;
    AbstractWidget* parent;

    virtual void RenderWidget();
    virtual void TearDown();

    static unsigned int nextElementId;
    static unsigned int generateId();
};
