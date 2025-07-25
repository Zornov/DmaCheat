#include <iostream>
#include <Memory/Memory.h>

int main() {
    if (!mem.Init("discord.exe", true, false)) {
        std::cout << "DMA initialization error" << std::endl;
        system("pause");
        return 1;
    }
    std::cout << "DMA initialized successfully" << std::endl;

    system("pause");
    return 0;
}