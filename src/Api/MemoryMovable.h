//
// Created by Erik on 09/04/22.
//

#ifndef LII_MEMORYMOVABLE_H
#define LII_MEMORYMOVABLE_H

template<class T>
class MemoryMovable
{
public:
    virtual void Move(const T&) = 0;
};


#endif //LII_MEMORYMOVABLE_H
