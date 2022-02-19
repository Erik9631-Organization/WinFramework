//
// Created by Erik on 19/02/22.
//

#ifndef LII_UNIFORM_H
#define LII_UNIFORM_H
class UniformManager;

class Uniform
{
public:
    virtual const UniformManager& GetUniformManager() = 0;
};


#endif //LII_UNIFORM_H
