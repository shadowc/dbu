// DBU.cpp : Defines the entry point for the application.
//

#include "DBU.h"
#include "Application.h"

using namespace Console;
using namespace std;

int main()
{
    Application::Initialize();
    Application::Run();
    Application::Shutdown();

    return 0;
}
