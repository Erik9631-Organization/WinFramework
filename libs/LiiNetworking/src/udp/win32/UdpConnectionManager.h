//
// Created by erik9 on 6/22/2023.
//

#ifndef LIINETWORKING_UDPCONNECTIONMANAGER_H
#define LIINETWORKING_UDPCONNECTIONMANAGER_H
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <string>
#include <vector>
#include <array>
#include <thread>
#include "ReceiverSubject.h"

namespace Lii::Udp
{

    class UdpConnectionManager : public Api::ReceiverSubject
    {
    private:
        static constexpr unsigned int bufferSize = 65536;
        SOCKET srcUdpSocket;
        sockaddr_in srcProperties;
        sockaddr_in dstProperties;
        unsigned int maxDatagramSize = 1400;
        std::vector<Api::ReceiverSubscriber*> receiverSubscribers;
        std::array<unsigned char, bufferSize> dataFrontBuffer;
        std::array<unsigned char, bufferSize> dataBackBuffer;
        std::unique_ptr<std::thread> receiveThread;
        bool receiveStarted = false;

    void CreateSocket(const std::string &targetIp, unsigned short targetPort);
    public:
        UdpConnectionManager(const std::string &listenIp, unsigned int listenPort);

        void StartConcurrentReceive();

        void FinishConcurrentReceive();

        void WaitForReceiveThread();

        void AddReceiverSubscriber(Api::ReceiverSubscriber &receiverSubscriber) override;

        void RemoveReceiverSubscriber(Api::ReceiverSubscriber &receiverSubscriber) override;

        void NotifyChunkReceived(unsigned char *streamBuffer, unsigned int size) override;

        void SendData(unsigned char *data, unsigned int totalPayloadSize) const;
        void SetDestination(const std::string &targetIp, unsigned short targetPort);
    };

} // Udp

#endif //LIINETWORKING_UDPCONNECTIONMANAGER_H
