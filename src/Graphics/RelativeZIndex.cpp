#include "RelativeZIndex.h"
#include <iostream>
RelativeZIndex* RelativeZIndex::instance = new RelativeZIndex();


[[maybe_unused]] void RelativeZIndex::RegisterIndex(const std::string &name, float index)
{

}

RelativeZIndex::RelativeZIndex()
{
    relativeIndexList["TextIndex"] = 0.0f;
    relativeIndexList["BorderIndex"] = 1.0f;
    relativeIndexList["BackgroundIndex"] = 2.0f;
}

RelativeZIndex *RelativeZIndex::GetInstance()
{
    return instance;
}

size_t RelativeZIndex::GetSize()
{
    return relativeIndexList.size();
}

float RelativeZIndex::GetIndex(const std::string &name)
{
    auto it = relativeIndexList.find(name);
    if(it == relativeIndexList.end())
    {
        std::cout << "Index not found" << std::endl;
        return 0;
    }

    return it->second;
}

void RelativeZIndex::SetIndex(const std::string &name, float value)
{
    auto it = relativeIndexList.find(name);
    if(relativeIndexList.find(name) == relativeIndexList.end())
    {
        std::cout << "Index not found" << std::endl;
        return;
    }
    it->second = value;
}
