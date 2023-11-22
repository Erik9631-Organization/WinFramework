//
// Created by erik9 on 6/22/2023.
//

#ifndef LIINETWORKING_NETWORKING_H
#define LIINETWORKING_NETWORKING_H
#include <winsock2.h>
#include "UdpConnectionManager.h"


namespace Lii
{
    class Networking
    {
    private:
        static WSADATA wsaData;

    public:
        static WSADATA & GetWsaData();
        static void Init();
    };
}

#endif //LIINETWORKING_NETWORKING_H
