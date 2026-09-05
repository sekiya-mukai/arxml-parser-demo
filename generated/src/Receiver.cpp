#include "Receiver.hpp"

#include <arpa/inet.h>

#include <cstdint>
#include <iostream>

void Receiver::run()
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

    receiverAddr.sin_addr.s_addr =
        INADDR_ANY;

    bind(
        sock,
        reinterpret_cast<sockaddr*>(
            &receiverAddr),
        sizeof(receiverAddr));

    uint8_t data {};

    while(true)
    {
        recv(
            sock,
            &data,
            sizeof(data),
            0);

        std::cout
            << "[RX] "
            << static_cast<int>(data)
            << std::endl;
    }
}