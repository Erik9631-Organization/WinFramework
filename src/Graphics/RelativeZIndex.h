//
// Created by erik9 on 2/19/2023.
//

#ifndef LII_RELATIVEZINDEX_H
#define LII_RELATIVEZINDEX_H
#include <string>
#include <unordered_map>

class RelativeZIndex
{
private:
    RelativeZIndex();
    static RelativeZIndex* instance;
    std::unordered_map<std::string, float> relativeIndexList;
public:
    [[maybe_unused]] void RegisterIndex(const std::string& name, float index);
    float GetIndex(const std::string& name);
    static RelativeZIndex* GetInstance();
    size_t GetSize();

};

#endif //LII_RELATIVEZINDEX_H
