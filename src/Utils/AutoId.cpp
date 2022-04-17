//
// Created by Erik on 16/04/22.
//

#include "AutoId.h"
using namespace Utils;
unsigned long long int AutoId::id = 0;

unsigned long long int AutoId::AquireId()
{
    id++;
    return id;
}

void AutoId::Reset(const unsigned long long int &id)
{
    AutoId::id = id;
}
