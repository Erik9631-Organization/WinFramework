#include "LiiApplication.h"
#include <thread>
#include <Injector.hpp>
#include "WindowsCore.h"
#include "Core.h"
#include "GdiRenderer.h"
#include "WindowsBufferRenderer.h"
#include "SoftwareRenderer.h"

#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif


LiiApplication* LiiApplication::application = new LiiApplication();;

void LiiApplication::JoinThreads()
{
	for (auto& i : threads)
	{
        if(i.second->joinable())
            i.second->join();
	}
}
LiiApplication *LiiApplication::GetInstance()
{
    return application;
}

void LiiApplication::Init()
{
    LiiInjector::Injector::GetInstance().RegisterTransient<Core>([](const std::string& name, long style, Window* window)->LiiInjector::Injectable*
    {
        auto core = WindowsCore::Create({name , style, window});
        return core.release();
    });

    LiiInjector::Injector::GetInstance().RegisterTransient<Renderer>([]()->LiiInjector::Injectable*
    {
        return new SoftwareRenderer();
    });

//    LiiInjector::Injector::GetInstance().RegisterTransient<Renderer>([]()->LiiInjector::Injectable*
//    {
//        return new GdiRenderer();
//    });

    LiiInjector::Injector::GetInstance().RegisterTransient<BufferRenderer>([]()->LiiInjector::Injectable*
    {
        return new WindowsBufferRenderer();
    });
}
