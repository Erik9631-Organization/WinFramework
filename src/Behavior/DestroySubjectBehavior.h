//
// Created by Erik on 18/04/22.
//

#ifndef LII_DESTROYSUBJECTBEHAVIOR_H
#define LII_DESTROYSUBJECTBEHAVIOR_H
#include "DestroySubject.h"
#include "DestroySubscriber.h"
#include <vector>

class DestroySubjectBehavior : public DestroySubject
{
private:
    std::vector<DestroySubscriber*> subscribers;
public:
    void NotifyOnDestroy(DestroyEventInfo *e) override;
    void AddOnDestroySubscriber(DestroySubscriber *subscriber) override;
    void RemoveOnDestroySubscriber(DestroySubscriber *subscriber) override;

};


#endif //LII_DESTROYSUBJECTBEHAVIOR_H
