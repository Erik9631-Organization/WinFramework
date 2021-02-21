#pragma once
#include <string>
#include <any>
#include "ClassMethod.h"
template<class T>
class ReflectionContainer;

template<class T>
class Reflectable
{
public:
	virtual bool HasMethod(std::string method) = 0;
	virtual ReflectionContainer<T>& GetReflectionContainer() = 0;
};

