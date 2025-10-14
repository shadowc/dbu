#include "dialog-manager/DialogManager.h"
#include "Application.h"
#include "dialog-manager/DialogDef.h"
#include "widget/Dialog.h"
#include "widget/Screen.h"
#include "widget/HStack.h"
#include "widget/StackItem.h"
#include <vector>

using namespace std;

DialogManager::DialogManager()
{
    dialogs = vector<Dialog*>();

    Dialog* connectionDialog = new Dialog();
    connectionDialog->SetTitle(" Connect to server ");

    HStack* hStack = new HStack();

    StackItem* sidebar = new StackItem();
    sidebar->SetStackSize(20);
    hStack->AddChild(sidebar);

    StackItem* contents = new StackItem();
    hStack->AddChild(contents);

    connectionDialog->AddChild(hStack);

    dialogs.push_back(connectionDialog);
}

void DialogManager::AttachDialogsToScreen() const
{
    Screen* screen = Application::GetScreen();

    for (Dialog* dialog : dialogs) {
        screen->AddChild(dialog);
    }
}

void DialogManager::CloseDialogs() const
{
    for (Dialog* dialog : dialogs) {
        dialog->SetVisible(false);
    }
}

void DialogManager::ShowDialog(Dialogs dialogName)
{
    // we hide every other dialog to avoid causing repaints later
    for (int n = 0; n < (int) dialogs.size(); n++) {
        if (n != (int) dialogName) {
            dialogs.at((int) dialogName)->SetVisible(false);
        }
    }

    // finally setVisible to true will only repaint if visible was false
    Dialog* dialog = dialogs.at((int) dialogName);
    dialog->SetVisible(true);
    dialog->Focus();
}

Dialog* DialogManager::GetDialog(Dialogs dialogName) const
{
    return dialogs.at((int) dialogName);
}
