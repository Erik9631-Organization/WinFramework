#pragma once
#include <memory>
#include "AddSubject.h"
#include <vector>
template<class T>
class MultiTree : public AddSubject<T>
{
public:
	virtual MultiTree<T> * AddNode(std::unique_ptr<MultiTree<T>> node) = 0;
	virtual void SetParentNode(MultiTree<T> *parentNode) = 0;
	virtual int GetNodeCount() = 0;
	virtual std::vector<std::unique_ptr<MultiTree<T>>> & GetNodes() = 0;
	virtual MultiTree<T>& GetRootNode() = 0;
	virtual void Remove(int index) = 0;
	virtual bool IsRoot() = 0;
	virtual MultiTree<T> * GetParentNode() = 0;
	virtual MultiTree<T>& GetNode(int index) = 0;
	virtual T& GetValue() = 0;
    virtual T& Get(const int& index) = 0;
    virtual MultiTree<T> * Add(T& obj) = 0;
    virtual T& GetParent() = 0;
    virtual void Disown(const bool& state) = 0;
    virtual const bool& IsDisowned() = 0;

	virtual void NotifyOnAddInfo(EventOnAddInfo<T> e) = 0;
	virtual void AddOnAddSubscriber(OnAddSubscriber<T>& subscriber) = 0;
	virtual void RemoveOnAddSubscriber(OnAddSubscriber<T>& subscriber) = 0;
    virtual ~MultiTree() = default;
};

