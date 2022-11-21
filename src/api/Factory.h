//
// Created by erik9 on 11/15/2022.
//

#ifndef LII_FACTORY_H
#define LII_FACTORY_H
#include "RenderingProvider.h"
#include <memory>
#include <string>
#include "Taggable.h"
template<class T>
class Factory : public Taggable
{
public:
    virtual std::unique_ptr<T> Create() = 0;
    virtual std::unique_ptr<T> Create(std::any args) = 0;
    virtual ~Factory() = default;
};


#endif //LII_FACTORY_H
