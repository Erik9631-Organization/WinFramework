#pragma once
#include "Primitive.h"

template<class Type>
class ClassMethod : Primitive
{
private:
	void (Type::*methodAddress)();
	Type* targetClass;
public:
	template<typename ReturnType, typename ...Args>
	ClassMethod(std::string name, Type* instance, ReturnType(Type::*methodAddress)(Args ...)) : Primitive(name)
	{
		targetClass = instance;
		this->methodAddress = (void(Type::*)())methodAddress;
	}

	template<typename ReturnType, typename ...Args>
	ReturnType Invoke(Args ... args)
	{
		ReturnType(Type::*functionPointer)(Args ...) = (ReturnType(Type::*)(Args ...))(methodAddress);
		return (targetClass->*functionPointer)(args ...);
	}
};