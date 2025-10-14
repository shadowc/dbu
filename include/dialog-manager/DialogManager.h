#pragma once
#include <vector>
#include "DialogDef.h"

using namespace std;

class Dialog;

class DialogManager
{
public:
    DialogManager();
    void AttachDialogsToScreen() const;
    void CloseDialogs() const;
    void ShowDialog(Dialogs dialogName);

    Dialog* GetDialog(Dialogs dialogName) const;

private:
   vector<Dialog*> dialogs;

};
