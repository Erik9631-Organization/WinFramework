#pragma once
#include <memory>
template<class T>
class MultiTree
{
public:
	virtual void Add(MultiTree<T>& object) = 0;
	virtual void SetParent(MultiTree<T>* obj) = 0;
	virtual void Remove(MultiTree<T>& object) = 0;
	virtual MultiTree<T>& GetRoot() = 0;
	virtual void Remove(int index) = 0;
	virtual bool IsRoot() = 0;
	virtual MultiTree<T>* GetParent() = 0;
	virtual MultiTree<T>& Get(int index) = 0;
	virtual T GetValue() = 0;
};

