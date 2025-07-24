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

        void Reload() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.press('r')\r\n");
            comPort.write(cmd);
        }

        void MiddleClick() override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.click(2)\r\n");
            comPort.write(cmd);
        }

        void MoveSmooth(const int x, const int y, const int timeMs) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.move_smooth(%d, %d, %d)\r\n", x, y, timeMs);
            comPort.write(cmd);
        }

        void KeyPress(const int key) override {
            char cmd[1024] = { 0 };
            sprintf_s(cmd, "km.press(%d)\r\n", key);
            comPort.write(cmd);
        }
    };
}
