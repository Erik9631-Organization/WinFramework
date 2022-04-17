//
// Created by Erik on 05/04/22.
//

#ifndef LII_IDENTIFIABLE_H
#define LII_IDENTIFIABLE_H


class Identifiable
{
public:
    ~Identifiable() = default;
    virtual const unsigned long long int & GetId() const = 0;
};

#endif //LII_IDENTIFIABLE_H
