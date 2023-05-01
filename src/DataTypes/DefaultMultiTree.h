#pragma once
#include "MultiTree.h"
#include <vector>
#include <stack>
#include "OnAddHandler.h"
#include <memory>
class UiElement;

template <class T>
class DefaultMultiTree : public MultiTree<T>
{
private:
	std::vector<std::unique_ptr<MultiTree<T>>> elementList;
	MultiTree<T>* parent;
	OnAddHandler<T> onAddHandler;
	T* nodeObject;
public:
	DefaultMultiTree(T associatedObj);
	// Inherited via Container
	virtual void SetParentNode(MultiTree<T> *parent) override;
	virtual MultiTree<T> * AddNode(std::unique_ptr<MultiTree<T>> object) override;
	virtual void Remove(int index) override;
	virtual MultiTree<T>& GetRootNode() override;
	virtual bool IsRoot() override;
	virtual MultiTree<T> * GetParentNode() override;
	virtual MultiTree<T>& GetNode(int index) override;
    virtual int GetNodeCount() override;
    virtual void NotifyOnAddInfo(EventOnAddInfo<T> e) override;
    virtual void AddOnAddSubscriber(OnAddSubscriber<T>& subscriber) override;
    virtual void RemoveOnAddSubscriber(OnAddSubscriber<T>& subscriber) override;

	// Inherited via Container
	virtual T& GetValue() override;
    std::vector<std::unique_ptr<MultiTree<T>>> & GetNodes() override;
    T& Get(const int &index) override;
    MultiTree<T> * Add(T &obj) override;
    T& GetParent() override;
    ~DefaultMultiTree() override;
    void Disown(const bool &state) override;
    const bool &IsDisowned() override;
    bool disowned = false;
};

template<class T>
inline DefaultMultiTree<T>::DefaultMultiTree(T associatedObj)
{
    nodeObject = new T(std::move(associatedObj));
    parent = nullptr;
}

template<class T>
void DefaultMultiTree<T>::SetParentNode(MultiTree<T> *obj)
{
    parent = std::move(obj);
}

template <class T>
MultiTree<T> * DefaultMultiTree<T>::AddNode(std::unique_ptr<MultiTree<T>> object)
{
    T& value = object->GetValue();
    MultiTree<T>* treeNode = object.get();
    object->SetParentNode((MultiTree<T> *) this);
    elementList.push_back(std::move(object));
    onAddHandler.NotifyOnAddInfo(EventOnAddInfo<T>{&value, this});
    return treeNode;
}


template <class T> void DefaultMultiTree<T>::Remove(int index)
{
    auto elementIterator = elementList.begin() + index;
    elementList.erase(elementIterator);
}

template <class T> MultiTree<T>& DefaultMultiTree<T>:: GetRootNode()
{
    std::stack<MultiTree<T>*> treeStack = std::stack<MultiTree<T>*>();
    treeStack.push(this);
    while (treeStack.top() != nullptr)
        treeStack.push(treeStack.top()->GetParentNode());

    treeStack.pop(); //Remove the nullptr node
    return *treeStack.top();
}


template <class T> bool DefaultMultiTree<T>::IsRoot()
{
    if (GetParentNode() != nullptr)
        return false;

    return true;
}

template <class T>
MultiTree<T> * DefaultMultiTree<T>::GetParentNode()
{
    return parent;
}

template <class T> MultiTree<T>& DefaultMultiTree<T>::GetNode(int index)
{
    return *elementList.at(index);
}

template<class T>
inline int DefaultMultiTree<T>::GetNodeCount()
{
    return elementList.size();
}

template<class T>
inline void DefaultMultiTree<T>::NotifyOnAddInfo(EventOnAddInfo<T> e)
{
    onAddHandler.NotifyOnAddInfo(e);
}

template<class T>
inline void DefaultMultiTree<T>::AddOnAddSubscriber(OnAddSubscriber<T>& subscriber)
{
    onAddHandler.AddOnAddSubscriber(subscriber);
}

template<class T>
inline void DefaultMultiTree<T>::RemoveOnAddSubscriber(OnAddSubscriber<T>& subscriber)
{
    onAddHandler.RemoveOnAddSubscriber(subscriber);
}

template <class T> T& DefaultMultiTree<T>::GetValue()
{
    return *nodeObject;
}

template<class T>
std::vector<std::unique_ptr<MultiTree<T>>> & DefaultMultiTree<T>::GetNodes()
{
    return elementList;
}

template<class T>
T& DefaultMultiTree<T>::Get(const int &index)
{
    return elementList.at(index)->GetValue();
}

template<class T>
MultiTree<T> * DefaultMultiTree<T>::Add(T &obj)
 {
    auto tree = std::make_unique<DefaultMultiTree<T>>(std::move(obj));
    return AddNode(std::move(tree));
}

template<class T>
T& DefaultMultiTree<T>::GetParent()
{
    if(GetParentNode() == nullptr)
        return GetValue();
    return GetParentNode()->GetValue();
}

template<class T>
DefaultMultiTree<T>::~DefaultMultiTree()
{
    if(disowned == false)
        delete nodeObject;
}

template<class T>
void DefaultMultiTree<T>::Disown(const bool &state)
{
    disowned = state;
}

template<class T>
const bool &DefaultMultiTree<T>::IsDisowned()
{
    return disowned;
}

