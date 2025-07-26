
#pragma once
#include "IKmboxDriver.h"
#include "lib/net/KmboxNet.h"

namespace kmbox {
    class KmboxNetDriver final : public IKmboxDriver {
        char ipAddress[24]{};
        char portNumber[10]{};
        char deviceUuid[32]{};

    public:
        KmboxNetDriver(const char* ipAddr, const char* port, const char* uuid) {
            strcpy_s(ipAddress, ipAddr);
            strcpy_s(portNumber, port);
            strcpy_s(deviceUuid, uuid);
        }

        bool Initialize() override {
            return kmNet_init(ipAddress, portNumber, deviceUuid) == 0;
        }

        void Reload() override {
            kmNet_reboot();
        }

        void Move(const int x, const int y) override {
            kmNet_mouse_move(static_cast<short>(x), static_cast<short>(y));
        }

        void MoveSmooth(const int x, const int y, const int timeMs) override {
            kmNet_mouse_move_auto(x, y, timeMs);
        }

        void Click(MouseButton button) override {
            const int buttonMask = static_cast<int>(button);
            kmNet_mouse_all(buttonMask, 0, 0, 0);
            kmNet_mouse_all(0, 0, 0, 0);
        }

        void ScrollWheel(const int amount) override {
            kmNet_mouse_wheel(amount);
        }

        void KeyPress(const int key) override {
            kmNet_keydown(key);
            kmNet_keyup(key);
        }

        void KeyDown(const int key) override {
            kmNet_keydown(key);
        }

        void KeyUp(const int key) override {
            kmNet_keyup(key);
        }

        void EnableMonitoring(const bool enable) override {
            kmNet_monitor(enable ? 1 : 0);
        }


        bool IsButtonPressed(const MouseButton button) override {
            switch(button) {
                case MouseButton::Left: return kmNet_monitor_mouse_left() != 0;
                case MouseButton::Right: return kmNet_monitor_mouse_right() != 0;
                case MouseButton::Middle: return kmNet_monitor_mouse_middle() != 0;
                case MouseButton::Side1: return kmNet_monitor_mouse_side1() != 0;
                case MouseButton::Side2: return kmNet_monitor_mouse_side2() != 0;
                default: return false;
            }
        }

        bool IsKeyPressed(const short key) override {
            return kmNet_monitor_keyboard(key) != 0;
        }

        void MaskLeftButton(const bool enable) override {
            kmNet_mask_mouse_left(enable ? 1 : 0);
        }

        void MaskRightButton(const bool enable) override {
            kmNet_mask_mouse_right(enable ? 1 : 0);
        }

        void MaskMouseX(const bool enable) override {
            kmNet_mask_mouse_x(enable ? 1 : 0);
        }

        void MaskMouseY(const bool enable) override {
            kmNet_mask_mouse_y(enable ? 1 : 0);
        }

        void UnmaskAll() override {
            kmNet_unmask_all();
        }

        void SetLcdColor(const unsigned short rgb565) override {
            kmNet_lcd_color(rgb565);
        }

        void DisplayPictureBottom(const unsigned char* buffer) override {
            if (buffer) {
                kmNet_lcd_picture_bottom(const_cast<unsigned char*>(buffer));
            }
        }

        void DisplayPictureFull(const unsigned char* buffer) override {
            if (buffer) {
                kmNet_lcd_picture(const_cast<unsigned char*>(buffer));
            }
        }

        void ConfigureNetwork(const char* newIp, const unsigned short newPort) override {
            kmNet_setconfig(const_cast<char*>(newIp), newPort);
        }

        void ConfigureUsb(const unsigned short vid, const unsigned short pid) override {
            kmNet_setvidpid(vid, pid);
        }

        void EnableDebug(const short port, const bool enable) override {
            kmNet_debug(port, enable ? 1 : 0);
        }
    };
}