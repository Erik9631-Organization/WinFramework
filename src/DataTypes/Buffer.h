//
// Created by erik9 on 5/22/2023.
//

#ifndef LII_BUFFER_H
#define LII_BUFFER_H

namespace Lii::DataTypes
{
    template<class T>
    class Buffer
    {
    private:
        T *buffer = nullptr;
        unsigned int size = 0;
        unsigned int width = 0;
        unsigned int height = 0;
    public:
        T& operator[](unsigned int index)
        {
            return buffer[index];
        }

        T* GetOffset(unsigned int offset)
        {
            return buffer + offset;
        }

        T* GetBuffer()
        {
            return buffer;
        }
        [[nodiscard]] unsigned int GetSize() const
        {
            return size;
        }
        [[nodiscard]] unsigned int GetWidth() const
        {
            return width;
        }
        unsigned int GetHeight() const
        {
            return height;
        }
        Buffer() = default;
        Buffer(int width, int height, T* buffer) :
            width(width),
            height(height),
            buffer(buffer),
            size(width * height)
        {

        }

    };
}

#endif //LII_BUFFER_H
