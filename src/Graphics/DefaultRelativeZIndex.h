//
// Created by erik9 on 2/19/2023.
//

#ifndef LII_DEFAULTRELATIVEZINDEX_H
#define LII_DEFAULTRELATIVEZINDEX_H
#include <string>
#include <unordered_map>

class DefaultRelativeZIndex
{
private:
    DefaultRelativeZIndex();
    static DefaultRelativeZIndex* instance;
    std::unordered_map<std::string, float> relativeIndexList;
public:
    [[maybe_unused]] void RegisterIndex(const std::string& name, float index);
    float GetIndex(const std::string& name);
    void SetIndex(const std::string &name, float value);
    static DefaultRelativeZIndex* GetInstance();
    size_t GetSize();

};

#endif //LII_DEFAULTRELATIVEZINDEX_H
