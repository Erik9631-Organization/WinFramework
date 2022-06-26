//
// Created by Erik on 26/06/22.
//

#ifndef LII_LIGHT_H
#define LII_LIGHT_H
class Light
{
public:
    virtual void SetEnabled(const bool& State) = 0;
    virtual const bool & GetEnabled() = 0;
};

#endif //LII_LIGHT_H
