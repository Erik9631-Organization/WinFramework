#pragma once
#include <string>
#include <typeinfo>
#include "Graphics/SimpleBorder.h"
#include "Graphics/Text.h"
#include "Graphics/Background.h"
#include <unordered_map>
#include <functional>

class AccessTools
{
	/*
	* Circular depedency problem, needs solution
	*/

private:
	template<typename ReturnType, typename Type, typename ... Args>
	static std::unordered_map<std::string, ReturnType(Type::*)(Args ...)>convertionTable;
	 
	template<typename RealType, typename ReturnType, typename ... Args>
	static ReturnType HandleInvoke(std::string functionName, void* instance, Args ... args)
	{
//		RealType& target = static_cast<RealType&>(*((RealType*)instance));
//		if (target.HasMethod(functionName))
//			return target.GetReflectionContainer().template Invoke<ReturnType>(functionName, args ...);
        return ReturnType();
	}
public:
	template<typename ReturnType, typename Type, typename ... Args>
	static void RegisterClassMethod(Type& instance)
	{
		//convertionTable<ReturnType, Type, Args ...>[typeid(instance).name()] = &AccessTools::HandleInvoke<Type, ReturnType, Args ...>;
	}

	template<typename ReturnType, typename Type, typename ... Args>
	static ReturnType Invoke(std::string functionName, Type& instance, Args ... args)
	{
		if (strcmp(typeid(instance).name(), "class SimpleBorder") == 0)
		{
			return HandleInvoke<SimpleBorder, ReturnType>(functionName, (void*)&instance, args ...);
		}
		else if (strcmp(typeid(instance).name(), "class Text") == 0)
		{
			return HandleInvoke<Text, ReturnType>(functionName, (void*)&instance, args ...);
		}
		else if (strcmp(typeid(instance).name(), "class Background") == 0)
		{
			return HandleInvoke<Background, ReturnType>(functionName, (void*)&instance, args ...);
		}
		else if (strcmp(typeid(instance).name(), "class TrackbarGraphics") == 0)
		{
			return HandleInvoke<Background, ReturnType>(functionName, (void*)&instance, args ...);
		}
	}
};

