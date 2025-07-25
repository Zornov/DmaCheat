cmake_minimum_required(VERSION 4.0)
project(DmaCheat)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(ext/kmbox)
add_subdirectory(ext/DMALibrary)

add_executable(DmaCheat src/main.cpp)

target_link_libraries(DmaCheat PRIVATE
        KmboxLib
        DMALib
)

add_custom_command(TARGET DmaCheat POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE_DIR:DMALib>/dbghelp.dll
        $<TARGET_FILE_DIR:DMALib>/FTD3XX.dll
        $<TARGET_FILE_DIR:DMALib>/leechcore.dll
        $<TARGET_FILE_DIR:DMALib>/symsrv.dll
        $<TARGET_FILE_DIR:DMALib>/vmm.dll
        $<TARGET_FILE_DIR:DmaCheat>
)

set_target_properties(DmaCheat PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "D:/app/cheat"
)