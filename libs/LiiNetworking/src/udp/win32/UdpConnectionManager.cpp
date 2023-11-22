//
// Created by erik9 on 6/22/2023.
//

#include "UdpConnectionManager.h"
#include <iostream>

using namespace Lii::Udp;

UdpConnectionManager::UdpConnectionManager(const std::string &listenIp, unsigned int listenPort)
{
    CreateSocket(listenIp, listenPort);
}

void UdpConnectionManager::CreateSocket(const std::string &targetIp, unsigned short targetPort)
{
    srcProperties.sin_family = AF_INET;
    srcProperties.sin_port = htons(targetPort);
    inet_pton(AF_INET, targetIp.c_str(), &srcProperties.sin_addr);

    srcUdpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    auto error = bind(srcUdpSocket, (sockaddr*)&srcProperties, sizeof(srcProperties));
    if(error == SOCKET_ERROR)
        std::cout << "Failed to bind socket with the following error: " << WSAGetLastError() << std::endl;

}

void UdpConnectionManager::AddReceiverSubscriber(Lii::Api::ReceiverSubscriber &receiverSubscriber)
{
    receiverSubscribers.push_back(&receiverSubscriber);
}

void UdpConnectionManager::RemoveReceiverSubscriber(Lii::Api::ReceiverSubscriber &receiverSubscriber)
{
    receiverSubscribers.erase(std::remove(receiverSubscribers.begin(), receiverSubscribers.end(),
                                          &receiverSubscriber), receiverSubscribers.end());
}

void UdpConnectionManager::NotifyChunkReceived(unsigned char *streamBuffer, unsigned int size)
{
    for(auto receiverSubscriber : receiverSubscribers)
        receiverSubscriber->OnStreamStarted(streamBuffer, size);
}

void UdpConnectionManager::StartConcurrentReceive()
{
    receiveStarted = true;
    receiveThread = std::make_unique<std::thread>(std::thread([this] (){
        while(receiveStarted)
        {
            auto result = recv(srcUdpSocket, (char*)dataFrontBuffer.data(), bufferSize, 0);
            if(result > 0)
            {
                std::swap(dataFrontBuffer, dataBackBuffer);
                NotifyChunkReceived(dataBackBuffer.data(), result);
            }
        }
    }));
}

void UdpConnectionManager::FinishConcurrentReceive()
{
    receiveStarted = false;
}

void UdpConnectionManager::WaitForReceiveThread()
{
    receiveThread->join();
}

void UdpConnectionManager::SendData(unsigned char *data, unsigned int totalPayloadSize) const
{
    unsigned char* dataPtr = data;
    unsigned char* dataEnd = data + totalPayloadSize;
    while(dataPtr != dataEnd)
    {
        auto currentSize = totalPayloadSize;
        if(currentSize > maxDatagramSize)
            currentSize = maxDatagramSize;

        auto numberSent = sendto(srcUdpSocket, (char*)dataPtr, currentSize, 0, (sockaddr*)&dstProperties, sizeof(dstProperties));
        if(numberSent == SOCKET_ERROR)
        {
            std::cout << "Failed to send with socket error: " << WSAGetLastError() << std::endl;
        }
        dataPtr += numberSent;
        totalPayloadSize = totalPayloadSize - numberSent;
        std::cout << "Sent data: " << numberSent << std::endl;
    }
}

void UdpConnectionManager::SetDestination(const std::string &targetIp, unsigned short targetPort)
{
    dstProperties.sin_family = AF_INET;
    dstProperties.sin_port = htons(targetPort);
    inet_pton(AF_INET, targetIp.c_str(), &dstProperties.sin_addr);
}
