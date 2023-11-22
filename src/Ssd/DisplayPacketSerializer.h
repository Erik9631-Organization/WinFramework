//
// Created by erik9 on 8/20/2023.
//

#ifndef LII_DISPLAYPACKETSERIALIZER_H
#define LII_DISPLAYPACKETSERIALIZER_H


#include <vector>
#include "Position.h"

class DisplayPacketSerializer
{
public:
    DisplayPacketSerializer(Position begin, Position end, std::vector<uint8_t> data);
    std::vector<uint8_t> Serialize();

private:
    Position begin;
    Position end;
    std::vector<uint8_t> data;
};



#endif //LII_DISPLAYPACKETSERIALIZER_H
