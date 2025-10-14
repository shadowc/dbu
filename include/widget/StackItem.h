#pragma ocne
#include "widget/AbstractWidget.h"

class StackItem : AbstractWidget
{
public:
    void SetSize(int newSize);
    int GetSize() const;

private:
    int sizeInStack = 0;
};
