#include <iostream>
#include <thread>
#include <chrono>
#include <Factory.h>
#include <Windows.h>

#include "lib/net/HidTable.h"

void waitForEnter(const std::string& nextAction) {
    std::cout << "\nPress Enter to " << nextAction << "...\n";
    std::cin.get();
}

void testMouse(const std::unique_ptr<kmbox::IKmboxDriver>& driver) {
    std::cout << "\n=== Mouse Test ===\n";
    std::cout << "Will test: movement, smooth movement, clicks, and scroll\n";
    waitForEnter("start mouse test");

    // Basic movement
    std::cout << "Moving cursor to (100, 100)...\n";
    driver->Move(100, 100);
    waitForEnter("continue with smooth movement");

    // Smooth movement
    std::cout << "Performing smooth movement to (200, 200)...\n";
    driver->MoveSmooth(200, 200, 1000);
    waitForEnter("continue with left click");

    // Clicks
    std::cout << "Testing left click...\n";
    driver->LeftClick();
    waitForEnter("continue with right click");

    std::cout << "Testing right click...\n";
    driver->RightClick();
    waitForEnter("continue with middle click");

    std::cout << "Testing middle click...\n";
    driver->MiddleClick();
    waitForEnter("continue with scroll test");

    // Scroll wheel
    std::cout << "Testing scroll wheel (up and down)...\n";
    driver->ScrollWheel(120);  // up
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    driver->ScrollWheel(-120); // down

    std::cout << "\nMouse test completed!\n";
}

void testKeyboard(const std::unique_ptr<kmbox::IKmboxDriver>& driver) {
    std::cout << "\n=== Keyboard Test ===\n";
    std::cout << "Will test: single key press and key combinations\n";
    waitForEnter("start keyboard test");

    // Single key
    std::cout << "Pressing 'A' key...\n";
    driver->KeyPress(KEY_A);
    waitForEnter("continue with Shift+A combination");

    // Key combination
    std::cout << "Testing Shift + A combination...\n";
    driver->KeyDown(KEY_LEFTSHIFT);
    driver->KeyPress(KEY_A);
    driver->KeyUp(KEY_LEFTSHIFT);

    std::cout << "\nKeyboard test completed!\n";
}

int main() {
    const auto ip = "192.168.2.188";
    const auto port = "61697";
    const auto uuid = "FF313CAB";

    std::cout << "Initializing KmboxNet...\n";
    const auto driver = kmbox::Factory::CreateNetDriver(ip, port, uuid);

    if (!driver->Initialize()) {
        std::cout << "Failed to initialize KmboxNet\n";
        return 1;
    }

    std::cout << "KmboxNet successfully initialized!\n";
    waitForEnter("begin tests");

    // Tests
    testMouse(driver);
    testKeyboard(driver);

    waitForEnter("reboot device");
    std::cout << "Rebooting device...\n";
    driver->Reload();

    std::cout << "\nAll tests completed!\n";
    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}