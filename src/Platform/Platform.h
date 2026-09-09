#ifndef WR_PLATFORM_H
#define WR_PLATFORM_H

#include <stdbool.h>
#include "Utils/Math.h"

// Color definitions (from raylib)
#define PLATFORM_LIGHTGRAY  (WrColor){ 200, 200, 200, 255 }   // Light Gray
#define PLATFORM_GRAY       (WrColor){ 130, 130, 130, 255 }   // Gray
#define PLATFORM_DARKGRAY   (WrColor){ 80, 80, 80, 255 }      // Dark Gray
#define PLATFORM_YELLOW     (WrColor){ 253, 249, 0, 255 }     // Yellow
#define PLATFORM_GOLD       (WrColor){ 255, 203, 0, 255 }     // Gold
#define PLATFORM_ORANGE     (WrColor){ 255, 161, 0, 255 }     // Orange
#define PLATFORM_PINK       (WrColor){ 255, 109, 194, 255 }   // Pink
#define PLATFORM_RED        (WrColor){ 230, 41, 55, 255 }     // Red
#define PLATFORM_MAROON     (WrColor){ 190, 33, 55, 255 }     // Maroon
#define PLATFORM_GREEN      (WrColor){ 0, 228, 48, 255 }      // Green
#define PLATFORM_LIME       (WrColor){ 0, 158, 47, 255 }      // Lime
#define PLATFORM_DARKGREEN  (WrColor){ 0, 117, 44, 255 }      // Dark Green
#define PLATFORM_SKYBLUE    (WrColor){ 102, 191, 255, 255 }   // Sky Blue
#define PLATFORM_BLUE       (WrColor){ 0, 121, 241, 255 }     // Blue
#define PLATFORM_DARKBLUE   (WrColor){ 0, 82, 172, 255 }      // Dark Blue
#define PLATFORM_PURPLE     (WrColor){ 200, 122, 255, 255 }   // Purple
#define PLATFORM_VIOLET     (WrColor){ 135, 60, 190, 255 }    // Violet
#define PLATFORM_DARKPURPLE (WrColor){ 112, 31, 126, 255 }    // Dark Purple
#define PLATFORM_BEIGE      (WrColor){ 211, 176, 131, 255 }   // Beige
#define PLATFORM_BROWN      (WrColor){ 127, 106, 79, 255 }    // Brown
#define PLATFORM_DARKBROWN  (WrColor){ 76, 63, 47, 255 }      // Dark Brown
#define PLATFORM_WHITE      (WrColor){ 255, 255, 255, 255 }   // White
#define PLATFORM_BLACK      (WrColor){ 0, 0, 0, 255 }         // Black
#define PLATFORM_BLANK      (WrColor){ 0, 0, 0, 0 }           // Blank (Transparent)
#define PLATFORM_MAGENTA    (WrColor){ 255, 0, 255, 255 }     // Magenta
#define PLATFORM_RAYWHITE   (WrColor){ 245, 245, 245, 255 }   // My own White (raylib logo)

// Config flags (from raylib)
typedef enum {
    PLATFORM_FLAG_VSYNC_HINT         = 0x00000040,   // Set to try enabling V-Sync on GPU
    PLATFORM_FLAG_FULLSCREEN_MODE    = 0x00000002,   // Set to run program in fullscreen
    PLATFORM_FLAG_WINDOW_RESIZABLE   = 0x00000004,   // Set to allow resizable window
    PLATFORM_FLAG_WINDOW_UNDECORATED = 0x00000008,   // Set to disable window decoration (frame and buttons)
    PLATFORM_FLAG_WINDOW_HIDDEN      = 0x00000080,   // Set to hide window
    PLATFORM_FLAG_WINDOW_MINIMIZED   = 0x00000200,   // Set to minimize window (iconify)
    PLATFORM_FLAG_WINDOW_MAXIMIZED   = 0x00000400,   // Set to maximize window (expanded to monitor)
    PLATFORM_FLAG_WINDOW_UNFOCUSED   = 0x00000800,   // Set to window non focused
    PLATFORM_FLAG_WINDOW_TOPMOST     = 0x00001000,   // Set to window always on top
    PLATFORM_FLAG_WINDOW_ALWAYS_RUN  = 0x00000100,   // Set to allow windows running while minimized
    PLATFORM_FLAG_WINDOW_TRANSPARENT = 0x00000010,   // Set to allow transparent framebuffer
    PLATFORM_FLAG_WINDOW_HIGHDPI     = 0x00002000,   // Set to support HighDPI
    PLATFORM_FLAG_WINDOW_MOUSE_PASSTHROUGH = 0x00004000, // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
    PLATFORM_FLAG_BORDERLESS_WINDOWED_MODE = 0x00008000, // Set to run program in borderless windowed mode
    PLATFORM_FLAG_MSAA_4X_HINT       = 0x00000020,   // Set to try enabling MSAA 4X
    PLATFORM_FLAG_INTERLACED_HINT    = 0x00010000    // Set to try enabling interlaced video format (for V3D)
} PlatformConfigFlags;

// Key definitions (from raylib)
typedef enum {
    PLATFORM_KEY_NULL            = 0,        // Key: NULL, used for no key pressed
    // Alphanumeric keys
    PLATFORM_KEY_APOSTROPHE      = 39,       // Key: '
    PLATFORM_KEY_COMMA           = 44,       // Key: ,
    PLATFORM_KEY_MINUS           = 45,       // Key: -
    PLATFORM_KEY_PERIOD          = 46,       // Key: .
    PLATFORM_KEY_SLASH           = 47,       // Key: /
    PLATFORM_KEY_ZERO            = 48,       // Key: 0
    PLATFORM_KEY_ONE             = 49,       // Key: 1
    PLATFORM_KEY_TWO             = 50,       // Key: 2
    PLATFORM_KEY_THREE           = 51,       // Key: 3
    PLATFORM_KEY_FOUR            = 52,       // Key: 4
    PLATFORM_KEY_FIVE            = 53,       // Key: 5
    PLATFORM_KEY_SIX             = 54,       // Key: 6
    PLATFORM_KEY_SEVEN           = 55,       // Key: 7
    PLATFORM_KEY_EIGHT           = 56,       // Key: 8
    PLATFORM_KEY_NINE            = 57,       // Key: 9
    PLATFORM_KEY_SEMICOLON       = 59,       // Key: ;
    PLATFORM_KEY_EQUAL           = 61,       // Key: =
    PLATFORM_KEY_A               = 65,       // Key: A | a
    PLATFORM_KEY_B               = 66,       // Key: B | b
    PLATFORM_KEY_C               = 67,       // Key: C | c
    PLATFORM_KEY_D               = 68,       // Key: D | d
    PLATFORM_KEY_E               = 69,       // Key: E | e
    PLATFORM_KEY_F               = 70,       // Key: F | f
    PLATFORM_KEY_G               = 71,       // Key: G | g
    PLATFORM_KEY_H               = 72,       // Key: H | h
    PLATFORM_KEY_I               = 73,       // Key: I | i
    PLATFORM_KEY_J               = 74,       // Key: J | j
    PLATFORM_KEY_K               = 75,       // Key: K | k
    PLATFORM_KEY_L               = 76,       // Key: L | l
    PLATFORM_KEY_M               = 77,       // Key: M | m
    PLATFORM_KEY_N               = 78,       // Key: N | n
    PLATFORM_KEY_O               = 79,       // Key: O | o
    PLATFORM_KEY_P               = 80,       // Key: P | p
    PLATFORM_KEY_Q               = 81,       // Key: Q | q
    PLATFORM_KEY_R               = 82,       // Key: R | r
    PLATFORM_KEY_S               = 83,       // Key: S | s
    PLATFORM_KEY_T               = 84,       // Key: T | t
    PLATFORM_KEY_U               = 85,       // Key: U | u
    PLATFORM_KEY_V               = 86,       // Key: V | v
    PLATFORM_KEY_W               = 87,       // Key: W | w
    PLATFORM_KEY_X               = 88,       // Key: X | x
    PLATFORM_KEY_Y               = 89,       // Key: Y | y
    PLATFORM_KEY_Z               = 90,       // Key: Z | z
    PLATFORM_KEY_LEFT_BRACKET    = 91,       // Key: [
    PLATFORM_KEY_BACKSLASH       = 92,       // Key: '\'
    PLATFORM_KEY_RIGHT_BRACKET   = 93,       // Key: ]
    PLATFORM_KEY_GRAVE           = 96,       // Key: `
    // Function keys
    PLATFORM_KEY_SPACE           = 32,       // Key: Space
    PLATFORM_KEY_ESCAPE          = 256,      // Key: Esc
    PLATFORM_KEY_ENTER           = 257,      // Key: Enter
    PLATFORM_KEY_TAB             = 258,      // Key: Tab
    PLATFORM_KEY_BACKSPACE       = 259,      // Key: Backspace
    PLATFORM_KEY_INSERT          = 260,      // Key: Ins
    PLATFORM_KEY_DELETE          = 261,      // Key: Del
    PLATFORM_KEY_RIGHT           = 262,      // Key: Cursor right
    PLATFORM_KEY_LEFT            = 263,      // Key: Cursor left
    PLATFORM_KEY_DOWN            = 264,      // Key: Cursor down
    PLATFORM_KEY_UP              = 265,      // Key: Cursor up
    PLATFORM_KEY_PAGE_UP         = 266,      // Key: Page up
    PLATFORM_KEY_PAGE_DOWN       = 267,      // Key: Page down
    PLATFORM_KEY_HOME            = 268,      // Key: Home
    PLATFORM_KEY_END             = 269,      // Key: End
    PLATFORM_KEY_CAPS_LOCK       = 280,      // Key: Caps lock
    PLATFORM_KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
    PLATFORM_KEY_NUM_LOCK        = 282,      // Key: Num lock
    PLATFORM_KEY_PRINT_SCREEN    = 283,      // Key: Print screen
    PLATFORM_KEY_PAUSE           = 284,      // Key: Pause
    PLATFORM_KEY_F1              = 290,      // Key: F1
    PLATFORM_KEY_F2              = 291,      // Key: F2
    PLATFORM_KEY_F3              = 292,      // Key: F3
    PLATFORM_KEY_F4              = 293,      // Key: F4
    PLATFORM_KEY_F5              = 294,      // Key: F5
    PLATFORM_KEY_F6              = 295,      // Key: F6
    PLATFORM_KEY_F7              = 296,      // Key: F7
    PLATFORM_KEY_F8              = 297,      // Key: F8
    PLATFORM_KEY_F9              = 298,      // Key: F9
    PLATFORM_KEY_F10             = 299,      // Key: F10
    PLATFORM_KEY_F11             = 300,      // Key: F11
    PLATFORM_KEY_F12             = 301,      // Key: F12
    PLATFORM_KEY_LEFT_SHIFT      = 340,      // Key: Shift left
    PLATFORM_KEY_LEFT_CONTROL    = 341,      // Key: Control left
    PLATFORM_KEY_LEFT_ALT        = 342,      // Key: Alt left
    PLATFORM_KEY_LEFT_SUPER      = 343,      // Key: Super left
    PLATFORM_KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
    PLATFORM_KEY_RIGHT_CONTROL   = 345,      // Key: Control right
    PLATFORM_KEY_RIGHT_ALT       = 346,      // Key: Alt right
    PLATFORM_KEY_RIGHT_SUPER     = 347,      // Key: Super right
    PLATFORM_KEY_KB_MENU         = 348,      // Key: KB menu
    // Keypad keys
    PLATFORM_KEY_KP_0            = 320,      // Key: Keypad 0
    PLATFORM_KEY_KP_1            = 321,      // Key: Keypad 1
    PLATFORM_KEY_KP_2            = 322,      // Key: Keypad 2
    PLATFORM_KEY_KP_3            = 323,      // Key: Keypad 3
    PLATFORM_KEY_KP_4            = 324,      // Key: Keypad 4
    PLATFORM_KEY_KP_5            = 325,      // Key: Keypad 5
    PLATFORM_KEY_KP_6            = 326,      // Key: Keypad 6
    PLATFORM_KEY_KP_7            = 327,      // Key: Keypad 7
    PLATFORM_KEY_KP_8            = 328,      // Key: Keypad 8
    PLATFORM_KEY_KP_9            = 329,      // Key: Keypad 9
    PLATFORM_KEY_KP_DECIMAL      = 330,      // Key: Keypad .
    PLATFORM_KEY_KP_DIVIDE       = 331,      // Key: Keypad /
    PLATFORM_KEY_KP_MULTIPLY     = 332,      // Key: Keypad *
    PLATFORM_KEY_KP_SUBTRACT     = 333,      // Key: Keypad -
    PLATFORM_KEY_KP_ADD          = 334,      // Key: Keypad +
    PLATFORM_KEY_KP_ENTER        = 335,      // Key: Keypad Enter
    PLATFORM_KEY_KP_EQUAL        = 336,      // Key: Keypad =
    // Android key buttons
    PLATFORM_KEY_BACK            = 4,        // Key: Android back button
    PLATFORM_KEY_MENU            = 5,        // Key: Android menu button
    PLATFORM_KEY_VOLUME_UP       = 24,       // Key: Android volume up button
    PLATFORM_KEY_VOLUME_DOWN     = 25        // Key: Android volume down button
} PlatformKeyboardKey;

// Abstraction functions
void PlatformSetConfigFlags(unsigned char flags);
void PlatformInitializeWindow(int w, int h, const char* title);
void PlatformSetTargetFPS(int fps);
bool PlatformWindowShouldClose();
void PlatformCloseWindow();

void PlatformBeginDrawing();
void PlatformEndDrawing();
void PlatformClearBackground(WrColor col);
void PlatformDrawFPS(int x, int y);

bool PlatformIsKeyDown(int key);
bool PlatformIsKeyPressed(int key);

void PlatformDrawLine(WrVector2 p1, WrVector2 p2, WrColor col);
void PlatformDrawRectangle(WrVector2 tlp, int w, int h, WrColor col);
void PlatformDrawCircle(WrVector2 center, float radius, WrColor col);

#endif // WR_PLATFORM_H