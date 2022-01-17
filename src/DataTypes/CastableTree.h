#pragma once
#include "MultiTree.h"
#include "DefaultMultiTree.h"
#include <any>

/*
* Experimental. Doesn't work, dont use!
*/

template <class T>
class CastableTree : public MultiTree<T>
{
private:
	DefaultMultiTree<std::any>* internalTree;
public:
	CastableTree(T associatedNode);
	~CastableTree();
	// Inherited via MultiTree
	virtual void Add(MultiTree<T>& object) override;
	virtual void SetParent(MultiTree<T>* obj) override;
	virtual void Remove(MultiTree<T>& object) override;
	virtual int GetNodeCount() override;
	virtual MultiTree<T>& GetRoot() override;
	virtual void Remove(int index) override;
	virtual bool IsRoot() override;
	virtual MultiTree<T>* GetParent() override;
	virtual MultiTree<T>& Get(int index) override;
	virtual T GetValue() override;
};

template<class T>
inline CastableTree<T>::CastableTree(T associatedNode) 
{
	internalTree = new DefaultMultiTree<std::any>(std::make_any(associatedNode));
}

template<class T>
inline CastableTree<T>::~CastableTree()
{
	delete internalTree;
}

template<class T>
inline void CastableTree<T>::Add(MultiTree<T>& object)
{
	internalTree->Add((MultiTree<std::any>&)object);
}

template<class T>
inline void CastableTree<T>::SetParent(MultiTree<T>* obj)
{
	internalTree->SetParent( (MultiTree<std::any>*) obj);
}

template<class T>
inline void CastableTree<T>::Remove(MultiTree<T>& object)
{
	internalTree->Remove((MultiTree<std::any>&) object);
}

template<class T>
inline int CastableTree<T>::GetNodeCount()
{
	return internalTree->GetNodeCount();
}

template<class T>
inline MultiTree<T>& CastableTree<T>::GetRoot()
{
	return (MultiTree<T>&) internalTree->GetRoot();
}

template<class T>
inline void CastableTree<T>::Remove(int index)
{
	internalTree->Remove(index);
}

template<class T>
inline bool CastableTree<T>::IsRoot()
{
	return internalTree->IsRoot();
}

template<class T>
inline MultiTree<T>* CastableTree<T>::GetParent()
{
	return (MultiTree<T>*) internalTree->GetParent();
}

template<class T>
inline MultiTree<T>& CastableTree<T>::Get(int index)
{
	return (MultiTree<T>&) internalTree->Get(index);
}

template<class T>
inline T CastableTree<T>::GetValue()
{
	T value = std::any_cast<T>(internalTree->GetValue());
	return value;
}

