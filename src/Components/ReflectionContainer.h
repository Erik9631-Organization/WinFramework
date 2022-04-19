#pragma once
#include "Reflectable.h"
#include <unordered_map>
#include <string>
#include "MetaObjects/ClassMethod.h"

template<class Type>
class ReflectionContainer
{
private:
	Type& associatedInstance;
	std::unordered_map<std::string, ClassMethod<Type>*>methods;
public:
	ReflectionContainer(Type& instance) : associatedInstance(instance)
	{

	}
	template<typename ... Args, typename ReturnType>
	void RegisterMethod(std::string accessName, std::string methodName, ReturnType (Type::*methodAddress)(Args ...))
	{
		methods[accessName] = new ClassMethod<Type>(accessName, &associatedInstance, methodAddress);
		//AccessTools::RegisterClassMethod<ReturnType, Type, Args...>(associatedInstance);

	}
	template<typename ReturnType, typename ... Args>
	ReturnType Invoke(std::string accessName, Args ... args)
	{
		return methods[accessName]->template Invoke<ReturnType>(args ...);
	}

	bool HasMethod(std::string method)
	{
		if (methods.find(method) == methods.end())
			return false;
		return true;
	}

};

