#include "ApplicationController.h"
#include "DemoApplication.h"
using namespace std;

int main()
{
    DemoApplication::LaunchDemoApp();
    ApplicationController::GetApplicationController()->JoinThreads();
    return 0;
}