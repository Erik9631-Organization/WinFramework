//
// Created by erik9 on 7/25/2023.
//

#ifndef LIINETWORKING_RECEIVERSUBSCRIBER_H
#define LIINETWORKING_RECEIVERSUBSCRIBER_H

namespace Lii::Api
{

    class ReceiverSubscriber
    {
    public:
        virtual void OnStreamStarted(unsigned char* streamBuffer, unsigned int size) = 0;
    };

} // Api

#endif //LIINETWORKING_RECEIVERSUBSCRIBER_H
