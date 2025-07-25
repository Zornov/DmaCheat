cmake_minimum_required(VERSION 4.0)
project(DmaCheat)

set(CMAKE_CXX_STANDARD 20)

add_library(KmboxNet STATIC
        ext/kmbox/lib/net/KmboxNet.cpp
        ext/kmbox/impl/KmboxNetDriver.h
)

target_include_directories(KmboxNet PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ext/kmbox
)

add_executable(DmaCheat src/main.cpp
        ext/kmbox/IKmboxDriver.h
        ext/kmbox/Factory.h
        ext/kmbox/Factory.cpp
        ext/kmbox/impl/KmboxNetDriver.h
        ext/kmbox/impl/KmboxBProDriver.h
)

target_include_directories(DmaCheat PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ext/kmbox
)

target_link_libraries(DmaCheat PRIVATE
        KmboxNet
        Ws2_32
)

set_target_properties(DmaCheat PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "D:/app/cheat"
)