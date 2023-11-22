#include <cstdint>
#include "DisplayPacketSerializer.h"


DisplayPacketSerializer::DisplayPacketSerializer(Position begin, Position end, std::vector<uint8_t> data)
        : begin(begin)
        , end(end)
        , data(data)
{

}

std::vector<uint8_t> DisplayPacketSerializer::Serialize()
{
    std::vector<uint8_t> buffer;

    buffer.insert(buffer.end(), begin.column());
    buffer.insert(buffer.end(), begin.page());

    buffer.insert(buffer.end(), end.column());
    buffer.insert(buffer.end(), end.page());

    buffer.insert(buffer.end(), data.begin(), data.end());

    return buffer;
}