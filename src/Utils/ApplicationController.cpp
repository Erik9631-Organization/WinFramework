#include "ApplicationController.h"
#include <thread>
#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif


ApplicationController* ApplicationController::applicationController = new ApplicationController();;

void ApplicationController::JoinThreads()
{
	for (auto& i : threads)
	{
        if(i.second->joinable())
            i.second->join();
	}
}
ApplicationController *ApplicationController::GetApplicationController()
{
    return applicationController;
}
