
#pragma once
#include <cstdio>
#include "../IKmboxDriver.h"
#include "lib/bpro/KmboxB.h"

namespace kmbox {
    class KmboxBProDriver final : public IKmboxDriver {
        _com comPort;
        int portNumber;

    public:
        explicit KmboxBProDriver(const int comPort) : portNumber(comPort) {}

        bool Initialize() override {
            return comPort.open(portNumber, 115200);
        }

        void Move(const int x, const int y) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.move(%d, %d, 10)\r\n", x, y);
            comPort.write(cmd);
        }

        void MoveSmooth(const int x, const int y, const int timeMs) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.move_smooth(%d, %d, %d)\r\n", x, y, timeMs);
            comPort.write(cmd);
        }

        void Click(MouseButton button) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.click(%d)\r\n", static_cast<int>(std::log2(static_cast<int>(button))));
            comPort.write(cmd);
        }

        void ScrollWheel(const int amount) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.wheel(%d)\r\n", amount);
            comPort.write(cmd);
        }

        void KeyPress(const int key) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.press(%d)\r\n", key);
            comPort.write(cmd);
        }

        void KeyDown(const int key) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.down(%d)\r\n", key);
            comPort.write(cmd);
        }

        void KeyUp(const int key) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.up(%d)\r\n", key);
            comPort.write(cmd);
        }

        void EnableMonitoring(const bool enable) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.monitor(%d)\r\n", enable ? 1 : 0);
            comPort.write(cmd);
        }

        bool IsButtonPressed(const MouseButton button) override {
            const char* cmdStr;
            switch(button) {
                case MouseButton::Left: cmdStr = "km.is_left()\r\n"; break;
                case MouseButton::Right: cmdStr = "km.is_right()\r\n"; break;
                case MouseButton::Middle: cmdStr = "km.is_middle()\r\n"; break;
                case MouseButton::Side1: cmdStr = "km.is_side1()\r\n"; break;
                case MouseButton::Side2: cmdStr = "km.is_side2()\r\n"; break;
                default: return false;
            }

            char cmd[1024] = { 0 };
            sprintf_s(cmd, "%s", cmdStr);
            comPort.write(cmd);

            char response[32] = { 0 };
            comPort.read(response, sizeof(response));
            return response[0] == '1';
        }

        bool IsKeyPressed(const short key) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.is_key(%d)\r\n", key);
            comPort.write(cmd);

            char response[32] = { 0 };
            comPort.read(response, sizeof(response));
            return response[0] == '1';
        }

        void MaskLeftButton(const bool enable) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.mask_left(%d)\r\n", enable ? 1 : 0);
            comPort.write(cmd);
        }

        void MaskRightButton(const bool enable) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.mask_right(%d)\r\n", enable ? 1 : 0);
            comPort.write(cmd);
        }

        void MaskMouseX(const bool enable) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.mask_x(%d)\r\n", enable ? 1 : 0);
            comPort.write(cmd);
        }

        void MaskMouseY(const bool enable) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.mask_y(%d)\r\n", enable ? 1 : 0);
            comPort.write(cmd);
        }

        void UnmaskAll() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.unmask_all()\r\n");
            comPort.write(cmd);
        }

        void Reload() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.reboot()\r\n");
            comPort.write(cmd);
        }

        void SetLcdColor(const unsigned short rgb565) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.lcd_color(%u)\r\n", rgb565);
            comPort.write(cmd);
        }

        void DisplayPictureBottom(const unsigned char* buffer) override {
            if (buffer) {
                char cmd[1024] = { 0 };
                sprintf_s(cmd, "km.lcd_bottom(%p)\r\n", buffer);
                comPort.write(cmd);
            }
        }

        void DisplayPictureFull(const unsigned char* buffer) override {
            if (buffer) {
                char cmd[1024] = { 0 };
                sprintf_s(cmd, "km.lcd_full(%p)\r\n", buffer);
                comPort.write(cmd);
            }
        }

        void ConfigureNetwork(const char* newIp, const unsigned short newPort) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.config_net(\"%s\", %u)\r\n", newIp, newPort);
            comPort.write(cmd);
        }

        void ConfigureUsb(const unsigned short vid, const unsigned short pid) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.config_usb(%u, %u)\r\n", vid, pid);
            comPort.write(cmd);
        }

        void EnableDebug(const short port, const bool enable) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.debug(%d, %d)\r\n", port, enable ? 1 : 0);
            comPort.write(cmd);
        }
    };
}