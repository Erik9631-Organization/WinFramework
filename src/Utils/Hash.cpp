//
// Created by Erik on 27/03/22.
//

#include "Hash.h"

unsigned int Utils::HashDjb2::CalculateHash(const std::string &inputString)
{
    unsigned int hash = 5381;
    char character = 0;
    char* stringArray = const_cast<char*>(inputString.data());

    while(character = *stringArray++)
        hash = ((hash << 5) + hash) + character;
    return hash;
}
