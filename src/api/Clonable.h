//
// Created by Erik on 09/04/22.
//

#ifndef LII_CLONABLE_H
#define LII_CLONABLE_H
#include <memory>
template<class T>
class Clonable
{
public:
    virtual std::unique_ptr<T> CloneUnique() const = 0;
    virtual std::shared_ptr<T> CloneShared() const = 0;
    virtual T* Clone() const = 0;
};


#endif //LII_CLONABLE_H
