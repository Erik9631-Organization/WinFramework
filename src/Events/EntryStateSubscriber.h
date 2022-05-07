//
// Created by Erik on 02/05/22.
//

#ifndef LII_ENTRYSTATESUBSCRIBER_H
#define LII_ENTRYSTATESUBSCRIBER_H

class EntryStateSubscriber
{
public:
    virtual void OnEntryStart() = 0;
    virtual void OnEntryEnd() = 0;
};


#endif //LII_ENTRYSTATESUBSCRIBER_H
