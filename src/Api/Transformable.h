//
// Created by Erik on 20/03/22.
//

#ifndef LII_TRANSFORMABLE_H
#define LII_TRANSFORMABLE_H
#include "Rotatable.h"
#include "Scalable.h"
#include "Translatable.h"

class Transformable : public Rotatable, public Scalable, public Translatable
{
public:
    virtual void ResetTransform() = 0;
};


#endif //LII_TRANSFORMABLE_H
