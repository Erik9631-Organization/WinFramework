//
// Created by Erik on 19/02/22.
//

#ifndef LII_GDIRENDERINGPOOL_H
#define LII_GDIRENDERINGPOOL_H
#include "RenderingPool.h"


class GdiRenderingPool : public RenderingPool
{
public:
    GdiRenderingPool(RenderingApi* renderer);
    RenderingApi &Acquire(const RenderCommander &target) override;
private:
    RenderingApi* renderer = nullptr;
};


#endif //LII_GDIRENDERINGPOOL_H
