//
// Created by Erik on 07/05/22.
//

#ifndef REDBLACKMEMORYMANAGER_METADATA_HPP
#define REDBLACKMEMORYMANAGER_METADATA_HPP
#include <any>

namespace MemManager
{
    class MetaData
    {
    private:
        size_t offset;
        size_t size;
        std::any userData;
    public:
        MetaData(const size_t offset, const size_t& size)
        {
            this->offset = offset;
            this->size = size;
            this->userData = nullptr;
        }

        template<typename DataType>
        const DataType GetUserData() const
        {
            return std::any_cast<DataType>(userData);
        }

        const size_t& GetOffset() const
        {
            return offset;
        }
        const size_t& GetSize() const
        {
            return size;
        }

        template<typename DataType>
        void SetUserData(DataType userData)
        {
            this->userData = std::make_any<DataType>(std::forward<DataType>(userData));
        }
    };

}


#endif //REDBLACKMEMORYMANAGER_METADATA_HPP
