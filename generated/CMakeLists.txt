cmake_minimum_required(VERSION 3.16)

project(
    CommunicationDemo
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    sender
    src/Sender.cpp
    src/SenderMain.cpp
)

target_include_directories(
    sender
    PRIVATE
        include
)

add_executable(
    receiver
    src/Receiver.cpp
    src/ReceiverMain.cpp
)

target_include_directories(
    receiver
    PRIVATE
        include
)