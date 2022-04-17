//
// Created by Erik on 27/03/22.
//

#ifndef LII_HASH_H
#define LII_HASH_H
#include <string>
#include <cstddef>

namespace Utils
{
    class HashDjb2
    {
    public:
        static unsigned int CalculateHash(const std::string& inputString);
    };
    template <class T>
    static inline void hash_combine(std::size_t& resultHash, const T& secondHash)
    {
        std::hash<T> hasher;
        resultHash ^= hasher(secondHash) + 0x9e3779b9 + (resultHash << 6) + (resultHash >> 2);
    }
}


#endif //LII_HASH_H
