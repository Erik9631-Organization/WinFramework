//
// Created by Erik on 08/10/22.
//

#ifndef LII_PRESENTER_H
#define LII_PRESENTER_H
#include "Movable.h"
#include "EventMouseStateInfo.h"
#include "MouseStateSubject.h"
#include "KeyStateSubject.h"
#include "Resizable.h"

class Presenter : public Movable, public Resizable, public MouseStateSubject, public KeyStateSubject
{

};


#endif //LII_PRESENTER_H
