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
/**
 * TODO Multi tree quality of life
 * Fix all the reference and pointer discrepencies
 * fix the need to have every component implement access to the element node.
 * The tree should receive the type and should automatically wrap the object into a tree node.
 * The nodes should be hidden away from the user
 */

class Element3d : public Transformable, public RenderCommander, public OnTickSubscriber, public TickSubject
{
public:
    virtual void Add(Element3d* element) = 0;
    virtual MultiTree<Element3d*>& GetElementNode() = 0;
};

#endif //LII_ELEMENT3D_H
