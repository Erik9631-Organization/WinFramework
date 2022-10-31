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
    const int& GetIndex() const;
    const long long int & GetValue() const;
    const std::any& GetSrc() const;
    EventAttributeInfo(const int& index,const long long int& value, std::any src);

};


#endif //LII_EVENTATTRIBUTEINFO_H
