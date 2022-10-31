//
// Created by Erik on 08/10/22.
//

#ifndef LII_EVENTCURSORLOCKINFO_H
#define LII_EVENTCURSORLOCKINFO_H
#include <any>

class EventCursorLockInfo
{
private:
    bool cursorLockInfo;
    std::any src;
public:
    EventCursorLockInfo(const bool& cursorLockInfo, std::any src);
    const std::any& GetSrc();
    const bool& GetCursorLockInfo();

};


#endif //LII_EVENTCURSORLOCKINFO_H
