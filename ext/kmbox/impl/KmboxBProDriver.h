
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

        void LeftClick() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.click(0)\r\n");
            comPort.write(cmd);
        }

        void RightClick() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.click(1)\r\n");
            comPort.write(cmd);
        }

        void MiddleClick() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.click(2)\r\n");
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

        bool IsLeftButtonPressed() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.is_left()\r\n");
            comPort.write(cmd);

            char response[32] = { 0 };
            comPort.read(response, sizeof(response));
            return response[0] == '1';
        }

        bool IsRightButtonPressed() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.is_right()\r\n");
            comPort.write(cmd);

            char response[32] = { 0 };
            comPort.read(response, sizeof(response));
            return response[0] == '1';
        }

        bool IsMiddleButtonPressed() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.is_middle()\r\n");
            comPort.write(cmd);

            char response[32] = { 0 };
            comPort.read(response, sizeof(response));
            return response[0] == '1';
        }

        bool IsSideButton1Pressed() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.is_side1()\r\n");
            comPort.write(cmd);

            char response[32] = { 0 };
            comPort.read(response, sizeof(response));
            return response[0] == '1';
        }

        bool IsSideButton2Pressed() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.is_side2()\r\n");
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