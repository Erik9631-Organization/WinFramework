#pragma once
#include <string>
#include <any>
#include "ClassMethod.h"
template<class TreeNode>
class ReflectionContainer;

template<class TreeNode>
class Reflectable
{
public:
	virtual bool HasMethod(std::string method) = 0;
	virtual ReflectionContainer<TreeNode>& GetReflectionContainer() = 0;
};

