//
// Created by Erik on 18/04/22.
//

#ifndef LII_ELEMENT3D_H
#define LII_ELEMENT3D_H
#include "Transformable.h"
#include "RenderCommander.h"
#include "OnTickSubscriber.h"
#include "TickSubject.h"
#include "MultiTree.h"
#include <memory>


class Element3d : public Transformable, public RenderCommander, public OnTickSubscriber, public TickSubject
{
public:
    virtual void Add(std::unique_ptr<Element3d> element) = 0;
    virtual MultiTree<std::unique_ptr<Element3d>> & GetElementNode() = 0;
    virtual ~Element3d() = default;
};

#endif //LII_ELEMENT3D_H
