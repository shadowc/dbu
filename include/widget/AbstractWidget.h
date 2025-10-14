#pragma once
#include "console/ConsoleDef.h"
#include "event/EventDef.h"
#include "widget/WidgetLayers.h"
#include <vector>
#include <string>

using namespace Console;
using namespace std;

class AbstractWidget {
public:
    AbstractWidget();
    ~AbstractWidget();

    virtual void Draw();

    Coords GetPosition();
    void SetPosition(Coords newCoords);
    void SetPosition(int x, int y);
    Size GetSize();
    void SetSize(Size newSize);
    void SetSize(int w, int h);
    virtual void Invalidate();
    virtual void OnResize();

    AbstractWidget* GetParent();
    virtual void SetParent(AbstractWidget*);
    void RemoveParent();
    virtual void AddChild(AbstractWidget* child);
    void RemoveChild(AbstractWidget* child);
    void RemoveChildAt(int index);
    int GetChildLength();
    AbstractWidget* GetChildAt(int index);

    virtual bool HasActiveMask();
    Mask GetActiveMask();

    string GetColorScheme();

    unsigned int GetUniqueId();

    bool HasFocus();
    void Focus();
    void Blur();

    void SetLayer(WidgetLayer newLayer);
    WidgetLayer GetLayer();

    virtual void OnEvent(Event& event);

protected:
    unsigned int uniqueId;
    bool invalidated;
    Coords coords;
    Size size;
    vector<AbstractWidget*> children;
    AbstractWidget* parent;
    string colorScheme;
    WidgetLayer layer = WidgetLayer::DEFAULT;

    void SetColorScheme(string newColorScheme);

    virtual void RenderWidget();
    virtual void TearDown();

    static unsigned int nextElementId;
    static unsigned int generateId();

    bool hasFocus = false;
};
