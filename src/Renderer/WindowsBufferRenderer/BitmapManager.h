//
// Created by erik9 on 5/16/2023.
//

#ifndef LII_BITMAPMANAGER_H
#define LII_BITMAPMANAGER_H
#include <windows.h>
#include <vector>
#include "glm.hpp"

class BitmapManager
{
private:
    HBITMAP bitmap = nullptr;
    unsigned int *buffer = nullptr;
    void Release();
    void CreateBitmap(HDC hdc);
    glm::ivec2 size{0};
public:
    BitmapManager(const glm::ivec2 &size, HDC hdc);

    void SetSize(const glm::ivec2 &size, HDC hdc);

    void DrawFragment(unsigned int x, unsigned int y, unsigned int hexColor);

    [[nodiscard]] const glm::ivec2 & GetSize();

    [[nodiscard]] unsigned int *GetBuffer() const;

    [[nodiscard]] HBITMAP GetBitmap() const;

    ~BitmapManager();
};

#endif //LII_BITMAPMANAGER_H
