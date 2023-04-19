#include "DefaultRelativeZIndex.h"
#include <iostream>
DefaultRelativeZIndex* DefaultRelativeZIndex::instance = new DefaultRelativeZIndex();


[[maybe_unused]] void DefaultRelativeZIndex::RegisterIndex(const std::string &name, float index)
{

}

DefaultRelativeZIndex::DefaultRelativeZIndex()
{
    relativeIndexList["TextIndex"] =  0.0f;
    relativeIndexList["None"] =  0.5f;
    relativeIndexList["BorderIndex"] = 1.0f;
    relativeIndexList["BackgroundIndex"] = 2.0f;
}

DefaultRelativeZIndex *DefaultRelativeZIndex::GetInstance()
{
    return instance;
}

size_t DefaultRelativeZIndex::GetSize()
{
    return relativeIndexList.size();
}

float DefaultRelativeZIndex::GetIndex(const std::string &name)
{
    auto it = relativeIndexList.find(name);
    if(it == relativeIndexList.end())
    {
        std::cout << "Index not found" << std::endl;
        return 0;
    }

    return it->second;
}

void DefaultRelativeZIndex::SetIndex(const std::string &name, float value)
{
    auto it = relativeIndexList.find(name);
    if(relativeIndexList.find(name) == relativeIndexList.end())
    {
        std::cout << "Index not found" << std::endl;
        return;
    }
    it->second = value;
}
