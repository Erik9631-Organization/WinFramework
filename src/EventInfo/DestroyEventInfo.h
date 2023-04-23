//
// Created by Erik on 12/04/22.
//

#ifndef LII_DESTROYEVENTINFO_H
#define LII_DESTROYEVENTINFO_H
#include <any>

class DestroyEventInfo
{
public:
    std::any src;
    template<class T>
    T* GetSrc()
    {
        return std::any_cast<T*>(src);
    }
};


#endif //LII_DESTROYEVENTINFO_H
