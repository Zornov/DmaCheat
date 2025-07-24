#pragma once
#include "IKmboxDriver.h"
#include "lib/net/KmboxNet.h"

namespace kmbox {
    class KmboxNetDriver final : public IKmboxDriver {
        char ip[24]{};
        char port[10]{};
        char uuid[32]{};

    public:
        KmboxNetDriver(const char* ip, const char* port, const char* uuid) {
            strcpy_s(this->ip, ip);
            strcpy_s(this->port, port);
            strcpy_s(this->uuid, uuid);
        }

        bool Initialize() override {
            return kmNet_init(ip, port, uuid) == 0;
        }

        void Move(const int x, const int y) override {
            kmNet_mouse_move(x, y);
        }

        void LeftClick() override {
            kmNet_mouse_left(1);
            kmNet_mouse_left(0);
        }

        void RightClick() override {
            kmNet_mouse_right(1);
            kmNet_mouse_right(0);
        }

        void Reload() override {
            kmNet_reboot();
        }

        void MiddleClick() override {
            kmNet_mouse_middle(1);
            kmNet_mouse_middle(0);
        }

        void ScrollWheel(const int amount) override {
            kmNet_mouse_wheel(amount);
        }

        void MoveSmooth(const int x, const int y, const int timeMs) override {
            kmNet_mouse_move_auto(x, y, timeMs);
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
    };
}
