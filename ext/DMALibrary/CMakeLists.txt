cmake_minimum_required(VERSION 4.0)
project(DMALib)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_compile_options(/wd4477 /wd4313)
endif()

add_library(DMALib STATIC
        Memory/Memory.cpp
        pch.cpp
)

target_include_directories(DMALib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Memory
)

target_link_libraries(DMALib
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/leechcore.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/vmm.lib
)

add_custom_command(TARGET DMALib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/dbghelp.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/FTD3XX.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/leechcore.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/symsrv.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/vmm.dll"
        $<TARGET_FILE_DIR:DMALib>
)