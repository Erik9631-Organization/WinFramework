#include "Position.h"

Position::Position()
    : posColumn(0)
    , posPage(0)
{
}

Position::Position(uint8_t column, uint8_t page)
    : posColumn(column)
    , posPage(page)
{
}

Position::Position(glm::ivec2& point): posColumn(point.x), posPage(point.y / 8)
{

}

void Position::setPosition(uint8_t column, uint8_t page)
{
    posColumn = column;
    posPage = page;
}

void Position::setColumn(uint8_t column)
{
    posColumn = column;
}

void Position::setPage(uint8_t page)
{
    posPage = page;
}

uint8_t& Position::rColumn()
{
    return posColumn;
}

uint8_t& Position::rPage()
{
    return posPage;
}

uint8_t Position::column() const
{
    return posColumn;
}

uint8_t Position::page() const
{
    return posPage;
}
