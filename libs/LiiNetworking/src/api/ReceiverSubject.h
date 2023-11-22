//
// Created by erik9 on 7/25/2023.
//

#ifndef LIINETWORKING_RECEIVERSUBJECT_H
#define LIINETWORKING_RECEIVERSUBJECT_H
#include "ReceiverSubscriber.h"

namespace Lii::Api
{
    class ReceiverSubject
    {
    public:
        virtual void AddReceiverSubscriber(ReceiverSubscriber& receiverSubscriber) = 0;
        virtual void RemoveReceiverSubscriber(ReceiverSubscriber& receiverSubscriber) = 0;
        virtual void NotifyChunkReceived(unsigned char* streamBuffer, unsigned int size) = 0;
    };
}

#endif //LIINETWORKING_RECEIVERSUBJECT_H
