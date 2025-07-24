#pragma once
#include <Winsock2.h>

#pragma warning(disable : 4996)

// Command codes
#define cmd_connect          0xaf3c2828 // ok connect to box
#define cmd_mouse_move       0xaede7345 // ok mouse move
#define cmd_mouse_left       0x9823AE8D // ok mouse left button control
#define cmd_mouse_middle     0x97a3AE8D // ok mouse middle button control
#define cmd_mouse_right      0x238d8212 // ok mouse right button control
#define cmd_mouse_wheel      0xffeead38 // ok mouse wheel control
#define cmd_mouse_automove   0xaede7346 // ok mouse auto simulated human move control
#define cmd_keyboard_all     0x123c2c2f // ok keyboard all parameter control
#define cmd_reboot           0xaa8855aa // ok reboot box
#define cmd_bazerMove        0xa238455a // ok mouse bezier move
#define cmd_monitor          0x27388020 // ok monitor physical mouse and keyboard data on box
#define cmd_debug            0x27382021 // ok enable debug info
#define cmd_mask_mouse       0x23234343 // ok mask physical mouse and keyboard
#define cmd_unmask_all       0x23344343 // ok unmask physical mouse and keyboard
#define cmd_setconfig        0x1d3d3323 // ok set IP configuration
#define cmd_setvidpid        0xffed3232 // ok set device VID PID
#define cmd_showpic          0x12334883 // show picture


extern SOCKET sockClientfd; // socket communication handle

// Command header structure
typedef struct
{
    unsigned int mac;       // box MAC address (mandatory)
    unsigned int rand;      // random value
    unsigned int indexpts;  // timestamp
    unsigned int cmd;       // command code
} cmd_head_t;

// Data buffer structure (8-bit)
typedef struct
{
    unsigned char buff[1024];
} cmd_data_t;

// Data buffer structure (16-bit)
typedef struct
{
    unsigned short buff[512];
} cmd_u16_t;

// Mouse data structure
typedef struct
{
    int button;
    int x;
    int y;
    int wheel;
    int point[10]; // reserved for Bezier curve control (up to 5th order derivatives)
} soft_mouse_t;

// Keyboard data structure
typedef struct
{
    char ctrl;
    char resvel;
    char button[10];
} soft_keyboard_t;

// Union structure for client transmission data
typedef struct
{
    cmd_head_t head;
    union {
        cmd_data_t      u8buff;       // 8-bit buffer
        cmd_u16_t       u16buff;      // 16-bit buffer
        soft_mouse_t    cmd_mouse;    // mouse command data
        soft_keyboard_t cmd_keyboard; // keyboard command data
    };
} client_tx;

// Error codes enumeration
enum
{
    err_creat_socket = -9000,  // socket creation failed
    err_net_version,           // socket version error
    err_net_tx,                // socket send error
    err_net_rx_timeout,        // socket receive timeout
    err_net_cmd,               // command error
    err_net_pts,               // timestamp error
    success = 0,               // success
    usb_dev_tx_timeout,        // USB device send timeout
};


/*
 Connect to kmboxNet box with parameters:
 ip   : IP address of the box (displayed on screen)
 port : communication port number (displayed on screen)
 mac  : MAC address of the box (displayed on screen)

 Returns: 0 on success, other values correspond to error codes
*/
int kmNet_init(char* ip, char* port, char* mac); // ok
int kmNet_mouse_move(short x, short y);           // ok
int kmNet_mouse_left(int isdown);                  // ok
int kmNet_mouse_right(int isdown);                 // ok
int kmNet_mouse_middle(int isdown);                // ok
int kmNet_mouse_wheel(int wheel);                   // ok
int kmNet_mouse_all(int button, int x, int y, int wheel); // ok
int kmNet_mouse_move_auto(int x, int y, int time_ms);     // ok
int kmNet_mouse_move_beizer(int x, int y, int ms, int x1, int y1, int x2, int y2); // 2nd order Bezier curve

// Keyboard functions
int kmNet_keydown(int vkey); // ok
int kmNet_keyup(int vkey);   // ok

// Monitoring functions
int kmNet_monitor(int enable);             // enable/disable physical mouse and keyboard monitoring
int kmNet_monitor_mouse_left();            // query physical mouse left button status
int kmNet_monitor_mouse_middle();          // query mouse middle button status
int kmNet_monitor_mouse_right();           // query mouse right button status
int kmNet_monitor_mouse_side1();            // query mouse side button 1 status
int kmNet_monitor_mouse_side2();            // query mouse side button 2 status
int kmNet_monitor_keyboard(short vk_key); // query specified keyboard key status

// Physical mouse and keyboard masking functions
int kmNet_mask_mouse_left(int enable);     // mask mouse left button
int kmNet_mask_mouse_right(int enable);    // mask mouse right button
int kmNet_mask_mouse_middle(int enable);   // mask mouse middle button
int kmNet_mask_mouse_side1(int enable);    // mask mouse side button 1
int kmNet_mask_mouse_side2(int enable);    // mask mouse side button 2
int kmNet_mask_mouse_x(int enable);        // mask mouse X axis
int kmNet_mask_mouse_y(int enable);        // mask mouse Y axis
int kmNet_mask_mouse_wheel(int enable);    // mask mouse wheel
int kmNet_mask_keyboard(short vkey);       // mask specified keyboard key
int kmNet_unmask_keyboard(short vkey);     // unmask specified keyboard key
int kmNet_unmask_all();                      // unmask all previously masked keys


// Configuration functions
int kmNet_reboot(void);                                        // reboot the box
int kmNet_setconfig(char* ip, unsigned short port);           // configure box IP address
int kmNet_setvidpid(unsigned short vid, unsigned short pid);  // set box VID/PID, requires reboot to take effect
int kmNet_debug(short port, char enable);                     // enable debug
int kmNet_lcd_color(unsigned short rgb565);                   // fill entire LCD with specified color; black to clear screen
int kmNet_lcd_picture_bottom(unsigned char* buff_128_80);     // display 128x80 picture on bottom half of LCD
int kmNet_lcd_picture(unsigned char* buff_128_160);           // display 128x160 picture on full LCD


// The following functions should NOT be called externally (hardware descriptors used to update all parameters on device side)
int kmNet_DevDescriptor(int wrflag, char* buff, int length);       // read/write device descriptor
int kmNet_CfgDescriptor(int wrflag, char* buff, int length);       // read/write configuration descriptor
int kmNet_EndPointDescriptor(int wrflag, int ep, char* buff, int length); // read/write endpoint descriptor


// Video capture functions (disabled)
#if 0
int kvm_setvideo(int width, int height, int fps);  // set video capture resolution and FPS
int kvm_getframe(Mat* frame);                       // get latest video frame
int kvm_load_yolo_module(char* path);               // load YOLO model path
int kvm_run_yolo(Mat* frame, int cpu_gpu);          // run inference
#endif
