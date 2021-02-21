#pragma once
#include <string>
#include <typeinfo>
#include "SimpleBorder.h"
#include "Text.h"
#include "Background.h"
#include <unordered_map>
#include <functional>
class AccessTools
{
private:
	template<typename RealType, typename ReturnType, typename Type, typename ... Args>
	static void HandleInvoke(std::string functionName, Type& instance, Args ... args)
	{
		RealType& target = static_cast<RealType&>(instance);
		if (target.HasMethod(functionName))
			target.GetReflectionContainer().Invoke<ReturnType>(functionName, args ...);
	}

public:
	template<typename ReturnType, typename Type, typename ... Args>
	static void Invoke(std::string functionName, Type& instance, Args ... args)
	{
		if (strcmp(typeid(instance).name(), "class SimpleBorder") == 0)
		{
			HandleInvoke<SimpleBorder, ReturnType>(functionName, instance, args ...);
		}
		else if (strcmp(typeid(instance).name(), "class Text") == 0)
		{
			HandleInvoke<Text, ReturnType>(functionName, instance, args ...);
		}
		else if (strcmp(typeid(instance).name(), "class Background") == 0)
		{
			HandleInvoke<Background, ReturnType>(functionName, instance, args ...);
		}
	}
};

