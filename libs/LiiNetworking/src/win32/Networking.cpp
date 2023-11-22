//
// Created by erik9 on 6/22/2023.
//
#include "Networking.h"
#include <iostream>
WSAData Lii::Networking::wsaData = WSAData();

void Lii::Networking::Init()
{
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != NO_ERROR)
        std::cout << "Failed to initialize networking with the following error: " << result << std::endl;
}

WSADATA &Lii::Networking::GetWsaData()
{
    return wsaData;
}
