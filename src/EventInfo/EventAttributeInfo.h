//
// Created by Erik on 08/10/22.
//

#ifndef LII_EVENTATTRIBUTEINFO_H
#define LII_EVENTATTRIBUTEINFO_H
#include <any>


class EventAttributeInfo
{
private:
    int index = 0;
    long long int value = 0;
    std::any src;
public:
    [[nodiscard]] int GetIndex() const;
    [[nodiscard]] long long int GetValue() const;
    [[nodiscard]] const std::any& GetSrc() const;
    EventAttributeInfo(int index, long long int value, const std::any &src);

};


#endif //LII_EVENTATTRIBUTEINFO_H
