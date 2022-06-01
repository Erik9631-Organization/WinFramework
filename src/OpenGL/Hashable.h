//
// Created by Erik on 27/03/22.
//

#ifndef LII_HASHABLE_H
#define LII_HASHABLE_H
#include <string>

class Hashable
{
public:
    virtual const size_t & GetHash() const = 0;
    virtual ~Hashable() = default;
};

#endif //LII_HASHABLE_H
