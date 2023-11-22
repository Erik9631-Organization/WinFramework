//
// Created by erik9 on 8/20/2023.
//

#ifndef LII_POSITION_H
#define LII_POSITION_H
#include "glm.hpp"
#include <cstdint>

class Position {
private:
    uint8_t posColumn;
    uint8_t posPage;

public:
    Position();
    // Position(Position position);
    Position(uint8_t column, uint8_t page);
    explicit Position(glm::ivec2& point);

    virtual ~Position() = default;

    void setPosition(uint8_t column, uint8_t page);

    void setColumn(uint8_t column);
    void setPage(uint8_t page);

    uint8_t& rColumn();
    uint8_t& rPage();

    [[nodiscard]] uint8_t column() const;
    [[nodiscard]] uint8_t page() const;

    bool operator==(Position& position) const
    {
        return posColumn == position.posColumn && posPage == position.posPage;
    }

    bool operator!=(Position& position) const
    {
        return !(*this == position);
    }
};

#endif //LII_POSITION_H
