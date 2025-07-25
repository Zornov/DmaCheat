
cmake_minimum_required(VERSION 4.0)
project(KmboxLib)

set(CMAKE_CXX_STANDARD 20)

add_library(KmboxLib STATIC
        lib/net/KmboxNet.cpp
        lib/bpro/KmboxB.h
        impl/KmboxNetDriver.h
        impl/KmboxBProDriver.h
        IKmboxDriver.h
        Factory.h
        Factory.cpp
)

target_include_directories(KmboxLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(KmboxLib PUBLIC
        Ws2_32
)