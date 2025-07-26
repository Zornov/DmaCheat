#include <iostream>
#include <Memory/Memory.h>
#include <Windows.h>
#include <thread>
#include <chrono>

constexpr uintptr_t dwLocalPlayer = 0x00946740;
constexpr uintptr_t m_iHealth = 0xC8;

void UpdateHealthScatter(const intptr_t clientDll) {
    int health = 0;
    uintptr_t playerPtr = 0;

    while (true) {
        auto handle = mem.CreateScatterHandle();

        mem.AddScatterReadRequest(handle, clientDll + dwLocalPlayer, &playerPtr, sizeof(playerPtr));
        mem.ExecuteReadScatter(handle);
        mem.CloseScatterHandle(handle);

        if (playerPtr) {
            handle = mem.CreateScatterHandle();
            mem.AddScatterReadRequest(handle, playerPtr + m_iHealth, &health, sizeof(health));
            mem.ExecuteReadScatter(handle);
            mem.CloseScatterHandle(handle);

            system("cls");
            std::cout << "==== Health Monitor (Scatter) ====" << std::endl;
            std::cout << "Player pointer: 0x" << std::hex << playerPtr << std::endl;
            std::cout << "Current health: " << std::dec << health << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

int main() {
    std::cout << "Initializing DMA..." << std::endl;

    if (!mem.Init("gmod.exe", true, false)) {
        std::cout << "DMA initialization error" << std::endl;
        std::cin.get();
        return 1;
    }
    std::cout << "DMA initialized successfully" << std::endl;

    const auto clientDll = mem.GetBaseAddress("client.dll");
    if (!clientDll) {
        std::cout << "Failed to get client.dll base address" << std::endl;
        std::cin.get();
        return 1;
    }
    std::cout << "Client DLL base address: 0x" << std::hex << clientDll << std::endl;

    std::thread healthThread(UpdateHealthScatter, clientDll);

    std::cin.get();
    TerminateThread(healthThread.native_handle(), 0);
    healthThread.detach();

    return 0;
}