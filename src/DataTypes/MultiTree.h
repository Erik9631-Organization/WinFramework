#pragma once
#include <memory>
#include "AddSubject.h"
#include <vector>
template<class T>
class MultiTree : AddSubject<T>
{
public:
	virtual void Add(MultiTree<T>& object) = 0;
	virtual void SetParent(MultiTree<T>* obj) = 0;
	virtual void Remove(MultiTree<T>& object) = 0;
	virtual int GetNodeCount() = 0;
	virtual std::vector<std::reference_wrapper<MultiTree<T>>>& GetNodes() = 0;
	virtual MultiTree<T>& GetRoot() = 0;
	virtual void Remove(int index) = 0;
	virtual bool IsRoot() = 0;
	virtual MultiTree<T>* GetParent() = 0;
	virtual MultiTree<T>& Get(int index) = 0;
	virtual T GetValue() = 0;

	virtual void NotifyOnAddInfo(EventOnAddInfo<T> e) = 0;
	virtual void AddOnAddSubscriber(OnAddSubscriber<T>& subscriber) = 0;
	virtual void RemoveOnAddSubscriber(OnAddSubscriber<T>& subscriber) = 0;
};

