#include <iostream>
#include <Memory/Memory.h>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <iomanip>

namespace Offsets {
    constexpr uintptr_t dwEntityList = 0x00940B08;
    constexpr uintptr_t dwViewMatrix = 0xA3F7F0;

    constexpr uintptr_t Health = 0xC8;          // m_iHealth
    constexpr uintptr_t MaxHealth = 0xCC;       // m_iMaxHealth
    constexpr uintptr_t VecOrigin = 0x428;      // m_vecOrigin
    constexpr uintptr_t Velocity = 0x148;       // velocity
}


struct Vector3 {
    float x, y, z;

    bool operator!=(const Vector3& other) const {
        constexpr float epsilon = 0.1f;
        return std::abs(x - other.x) > epsilon ||
               std::abs(y - other.y) > epsilon ||
               std::abs(z - other.z) > epsilon;
    }

    void Print(std::ostream& os) const {
        os << std::fixed << std::setprecision(1)
           << x << ", " << y << ", " << z;
    }
};

struct Matrix4x4 {
    float m[4][4];

    void Print(std::ostream& os) const {
        os << std::fixed << std::setprecision(3);
        for (int i = 0; i < 4; ++i) {
            os << "[ ";
            for (int j = 0; j < 4; ++j) {
                os << std::setw(8) << m[i][j] << " ";
            }
            os << "]\n";
        }
    }
};

struct PlayerInfo {
    int health;
    int maxHealth;
    int armor;
    int maxArmor;
    Vector3 position;
    Vector3 velocity;
    Vector3 viewAngles;
};

int main() {
    std::cout << "Initializing DMA...\n";

    if (!mem.Init("gmod.exe", true, false)) {
        std::cout << "DMA initialization error\n";
        std::cin.get();
        return 1;
    }

    std::cout << "DMA initialized successfully\n";

    const uintptr_t clientDll = mem.GetBaseAddress("client.dll");
    if (!clientDll) {
        std::cout << "Failed to get client.dll base address\n";
        std::cin.get();
        return 1;
    }

    while (true) {
        system("cls");

        const uintptr_t entityList = mem.Read<uintptr_t>(clientDll + Offsets::dwEntityList);
        if (!entityList) {
            std::cout << "Entity list is empty\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        const uintptr_t playerBase = mem.Read<uintptr_t>(entityList);
        if (!playerBase) {
            std::cout << "Player entity not found\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        PlayerInfo player{};

        player.health = mem.Read<int>(playerBase + Offsets::Health);
        player.maxHealth = mem.Read<int>(playerBase + Offsets::MaxHealth);
        player.position = mem.Read<Vector3>(playerBase + Offsets::VecOrigin);
        player.velocity = mem.Read<Vector3>(playerBase + Offsets::Velocity);

        std::cout << "Health: " << player.health << " / " << player.maxHealth << '\n';

        std::cout << "Position: ";
        player.position.Print(std::cout);
        std::cout << "\nVelocity: ";
        player.velocity.Print(std::cout);

        auto viewMatrix = mem.Read<Matrix4x4>(clientDll + Offsets::dwViewMatrix);
        std::cout << "View Matrix:\n";
        viewMatrix.Print(std::cout);


        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
