
#pragma once
#include "lib/net/HidTable.h"

namespace kmbox {
    /**
     * @brief The main interface for Kmbox devices
     *
     * Provides a unified interface for working with different
     * types of Kmbox devices (network and COM-port devices)
     */
    class IKmboxDriver {
    public:
        /**
        * @brief Mouse buttons enumeration with corresponding bit masks
        *
        * Each button is represented by its bit in the mouse state byte:
        * bit 0 (0x01) - left button
        * bit 1 (0x02) - right button
        * bit 2 (0x04) - middle button/wheel
        * bit 3 (0x08) - side button 1
        * bit 4 (0x10) - side button 2
        */
        enum class MouseButton {
            Left = BIT0,
            Right = BIT1,
            Middle = BIT2,
            Side1 = BIT3,
            Side2 = BIT4
        };

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
         * @brief Emulates a click with the specified mouse button
         * @param button Mouse button from MouseButton enum
         */
        virtual void Click(MouseButton button) = 0;

        /**
         * @brief Checks if the specified mouse button is currently pressed
         * @param button Mouse button from MouseButton enum
         * @return true if button is pressed, false otherwise
         */
        virtual bool IsButtonPressed(MouseButton button) = 0;

        /**
         * @brief Reboot the device
         */
        virtual void Reload() = 0;

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
         * @param key Key code (Check HidTable.h)
         */
        virtual void KeyPress(int key) { }

        /**
         * @brief Emulate key down event
         * @param key Key code (Check HidTable.h)
         */
        virtual void KeyDown(int key) { }

        /**
         * @brief Emulate key up event
         * @param key Key code (Check HidTable.h)
         */
        virtual void KeyUp(int key) { }

        /**
         * @brief Fill the LCD screen with a specific color
         * @param rgb565 Color in RGB565 format
         */
        virtual void SetLcdColor(unsigned short rgb565) { }

        /**
         * @brief Display an image on the bottom half of the LCD screen
         * @param buffer Image buffer (128x80 pixels)
         */
        virtual void DisplayPictureBottom(const unsigned char* buffer) { }

        /**
         * @brief Display an image on the full LCD screen
         * @param buffer Image buffer (128x160 pixels)
         */
        virtual void DisplayPictureFull(const unsigned char* buffer) { }

        /**
         * @brief Enable/disable device monitoring
         * @param enable true to enable monitoring
         */
        virtual void EnableMonitoring(bool enable) { }

        /**
         * @brief Check if a specific keyboard key is pressed
         * @param key Key code to check
         * @return true if pressed, false otherwise
         */
        virtual bool IsKeyPressed(short key) { return false; }

        /**
         * @brief Configure device network settings
         * @param ip New IP address
         * @param port New port number
         */
        virtual void ConfigureNetwork(const char* ip, unsigned short port) { }

        /**
         * @brief Configure device USB settings
         * @param vid Vendor ID
         * @param pid Product ID
         */
        virtual void ConfigureUsb(unsigned short vid, unsigned short pid) { }

        /**
         * @brief Enable/disable debug mode
         * @param port Debug port number
         * @param enable true to enable debug
         */
        virtual void EnableDebug(short port, bool enable) { }

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
