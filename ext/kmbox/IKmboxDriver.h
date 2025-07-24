#pragma once

namespace kmbox {
    /**
     * @brief The main interface for Kmbox devices
     *
     * Provides a unified interface for working with different
     * types of Kmbox devices (network and COM-port devices)
     */
    class IKmboxDriver {
    public:
        virtual ~IKmboxDriver() = default;


        /**
         * @brief Initialize the device
         * @return true if initialization is successful, false otherwise
         */
        virtual bool Initialize() = 0;


        /**
         * @brief Move the cursor by pixels from the current cursor position
         * @param x Relative X movement (how many pixels to move right/left from the current position)
         * @param y Relative Y movement (how many pixels to move up/down from the current position)
         */
        virtual void Move(int x, int y) = 0;

        /**
         * @brief Emulate the left mouse button click
         */
        virtual void LeftClick() = 0;

        /**
         * @brief Emulate the right mouse button click
         */
        virtual void RightClick() = 0;

        /**
         * @brief Reboot the device
         */
        virtual void Reload() = 0;

        /**
         * @brief Emulate the middle mouse button click
         */
        virtual void MiddleClick() { }

        /**
         * @brief Emulate mouse wheel scrolling
         * @param amount Scroll amount (positive - up, negative - down)
         */
        virtual void ScrollWheel(int amount) { }


        /**
         * @brief Smooth cursor movement by pixels from the current cursor position
         * @param x Relative X movement from current position
         * @param y Relative Y movement from current position
         * @param timeMs Movement duration in milliseconds
         */
        virtual void MoveSmooth(int x, int y, int timeMs) { }

        /**
         * @brief Emulate key press (press and release)
         * @param key Virtual key code (VK_*)
         */
        virtual void KeyPress(int key) { }

        /**
         * @brief Emulate key down event
         * @param key Virtual key code (VK_*)
         */
        virtual void KeyDown(int key) { }

        /**
         * @brief Emulate key up event
         * @param key Virtual key code (VK_*)
         */
        virtual void KeyUp(int key) { }

        /**
         * @brief Mask left mouse button
         * @param enable true to enable masking
         * @details When masked, physical button presses are ignored
         */
        virtual void MaskLeftButton(bool enable) { }

        /**
         * @brief Mask right mouse button
         * @param enable true to enable masking
         * @details When masked, physical button presses are ignored
         */
        virtual void MaskRightButton(bool enable) { }

        /**
         * @brief Mask mouse X-axis movement
         * @param enable true to enable masking
         * @details When masked, physical mouse movement on X-axis is ignored
         */
        virtual void MaskMouseX(bool enable) { }

        /**
         * @brief Mask mouse Y-axis movement
         * @param enable true to enable masking
         * @details When masked, physical mouse movement on Y-axis is ignored
         */
        virtual void MaskMouseY(bool enable) { }

        /**
         * @brief Remove all device masks
         * @details Restores normal operation of all masked inputs
         */
        virtual void UnmaskAll() { }
    };
}