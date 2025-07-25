#include <iostream>
#include <thread>
#include <chrono>
#include <Factory.h>


int main() {
    const auto ip = "192.168.2.188";
    const auto port = "61697";
    const auto uuid = "Info";

    std::cout << "Initializing KmboxNet...\n";
    const auto driver = kmbox::Factory::Create(ip, port, uuid);

    if (!driver->Initialize()) {
        std::cout << "Failed to initialize KmboxNet\n";
        return 1;
    }

    std::cout << "Kmbox successfully initialized!\n";

    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}
