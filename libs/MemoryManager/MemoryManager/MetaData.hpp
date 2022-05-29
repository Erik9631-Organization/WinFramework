//
// Created by Erik on 07/05/22.
//

#ifndef REDBLACKMEMORYMANAGER_METADATA_HPP
#define REDBLACKMEMORYMANAGER_METADATA_HPP

namespace MemManager
{
    template<class T>
    class MetaData
    {
    private:
        size_t offset;
        size_t size;
        T* userData = nullptr;
    public:
        MetaData(const size_t offset, const size_t& size)
        {
            this->offset = offset;
            this->size = size;
            this->userData = nullptr;
        }
        const T& GetUserData() const
        {
            return *userData;
        }

        const size_t& GetOffset() const
        {
            return offset;
        }
        const size_t& GetSize() const
        {
            return size;
        }
        void SetUserData(T* userData)
        {
            this->userData = userData;
        }
    };

}


#endif //REDBLACKMEMORYMANAGER_METADATA_HPP
