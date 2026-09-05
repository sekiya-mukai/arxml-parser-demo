#include "Sender.hpp"

#include <arpa/inet.h>

#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <thread>

void Sender::run()
{
    int sock =
        socket(
            AF_INET,
            SOCK_DGRAM,
            0);

    sockaddr_in receiverAddr {};

    receiverAddr.sin_family = AF_INET;

    receiverAddr.sin_port =
        htons(
            50001
        );

    inet_pton(
        AF_INET,
        "192.168.10.101",
        &receiverAddr.sin_addr);

    while(true)
    {
        sendto(
            sock,
            &counter_,
            sizeof(counter_),
            0,
            reinterpret_cast<sockaddr*>(
                &receiverAddr),
            sizeof(receiverAddr));

        std::cout
            << "[TX] "
            << static_cast<int>(counter_)
            << std::endl;

        if(counter_ == 255)
        {
            counter_ = 0;
        }
        else
        {
            ++counter_;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(
                100
            ));
    }
}