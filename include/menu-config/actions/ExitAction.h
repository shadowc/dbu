#pragma once
#include "AbstractAction.h"

class ExitAction : public AbstractAction
{
public:
    void Execute() override;
};
