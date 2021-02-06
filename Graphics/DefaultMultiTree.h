#pragma once
#include "MultiTree.h"
#include <vector>
#include <stack>
#include <memory>
class Component;

template <class T>
class DefaultMultiTree : public MultiTree<T>
{
private:
	std::vector<std::reference_wrapper<MultiTree<T>>> elementList;
	MultiTree<T>* parent;
	T nodeObject;
public:
	DefaultMultiTree(T associatedObj);
	// Inherited via Container
	virtual void SetParent(MultiTree<T>* parent) override;
	virtual void Add(MultiTree<T>& object) override;
	virtual void Remove(MultiTree<T>& object) override;
	virtual void Remove(int index) override;
	virtual MultiTree<T>& GetRoot() override;
	virtual bool IsRoot() override;
	virtual MultiTree<T>* GetParent() override;
	virtual MultiTree<T>& Get(int index) override;
    virtual int GetNodeCount() override;

	// Inherited via Container
	virtual T GetValue() override;
};


template<class T>
inline DefaultMultiTree<T>::DefaultMultiTree(T associatedObj) : nodeObject(associatedObj)
{
    parent = nullptr;
}

template<class T>
void DefaultMultiTree<T>::SetParent(MultiTree<T>* obj)
{
    parent = obj;
}

template <class T> void DefaultMultiTree<T>::Add(MultiTree<T>& object)
{
    elementList.push_back(object);
    object.SetParent((MultiTree<T>*)this);
}


template <class T> void DefaultMultiTree<T>::Remove(MultiTree<T>& object)
{
    std::vector<reference_wrapper<MultiTree<T>>>::iterator it = elementList.begin();
    for (int i = 0; i < elementList.size(); i++, it++)
    {
        if (&elementList.at(i).get() == &object)
            elementList.erase(it);
    }
}

template <class T> void DefaultMultiTree<T>::Remove(int index)
{
    std::vector<reference_wrapper<MultiTree<T>>>::iterator elementIterator = elementList.begin() + index;
    elementList.erase(elementIterator);
}

template <class T> MultiTree<T>& DefaultMultiTree<T>::GetRoot()
{
    std::stack<MultiTree<T>*> treeStack = std::stack<MultiTree<T>*>();
    treeStack.push(this);
    while (treeStack.top() != nullptr)
        treeStack.push(treeStack.top()->GetParent());

    treeStack.pop();
    return *treeStack.top();
}


template <class T> bool DefaultMultiTree<T>::IsRoot()
{
    if (GetParent() != nullptr)
        return false;

    return true;
}

template <class T> MultiTree<T>* DefaultMultiTree<T>::GetParent()
{
    return parent;
}

template <class T> MultiTree<T>& DefaultMultiTree<T>::Get(int index)
{
    return elementList.at(index);
}

template<class T>
inline int DefaultMultiTree<T>::GetNodeCount()
{
    return elementList.size();
}

template <class T> T DefaultMultiTree<T>::GetValue()
{
    return nodeObject;
}

