/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2023 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  \file SDL_scancode.h
 *
 *  Defines keyboard scancodes.
 */

#pragma once

/**
 *  \brief The SDL keyboard scancode representation.
 *
 *  Values of this type are used to represent keyboard keys, among other places
 *  in the \link SDL_Keysym::scancode key.keysym.scancode \endlink field of the
 *  SDL_Event structure.
 *
 *  The values in this enumeration are based on the USB usage page standard:
 *  https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
 */
typedef enum
{
    TIGRAF_KEY_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    TIGRAF_KEY_A = 4,
    TIGRAF_KEY_B = 5,
    TIGRAF_KEY_C = 6,
    TIGRAF_KEY_D = 7,
    TIGRAF_KEY_E = 8,
    TIGRAF_KEY_F = 9,
    TIGRAF_KEY_G = 10,
    TIGRAF_KEY_H = 11,
    TIGRAF_KEY_I = 12,
    TIGRAF_KEY_J = 13,
    TIGRAF_KEY_K = 14,
    TIGRAF_KEY_L = 15,
    TIGRAF_KEY_M = 16,
    TIGRAF_KEY_N = 17,
    TIGRAF_KEY_O = 18,
    TIGRAF_KEY_P = 19,
    TIGRAF_KEY_Q = 20,
    TIGRAF_KEY_R = 21,
    TIGRAF_KEY_S = 22,
    TIGRAF_KEY_T = 23,
    TIGRAF_KEY_U = 24,
    TIGRAF_KEY_V = 25,
    TIGRAF_KEY_W = 26,
    TIGRAF_KEY_X = 27,
    TIGRAF_KEY_Y = 28,
    TIGRAF_KEY_Z = 29,

    TIGRAF_KEY_1 = 30,
    TIGRAF_KEY_2 = 31,
    TIGRAF_KEY_3 = 32,
    TIGRAF_KEY_4 = 33,
    TIGRAF_KEY_5 = 34,
    TIGRAF_KEY_6 = 35,
    TIGRAF_KEY_7 = 36,
    TIGRAF_KEY_8 = 37,
    TIGRAF_KEY_9 = 38,
    TIGRAF_KEY_0 = 39,

    TIGRAF_KEY_RETURN = 40,
    TIGRAF_KEY_ESCAPE = 41,
    TIGRAF_KEY_BACKSPACE = 42,
    TIGRAF_KEY_TAB = 43,
    TIGRAF_KEY_SPACE = 44,

    TIGRAF_KEY_MINUS = 45,
    TIGRAF_KEY_EQUALS = 46,
    TIGRAF_KEY_LEFTBRACKET = 47,
    TIGRAF_KEY_RIGHTBRACKET = 48,
    TIGRAF_KEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    TIGRAF_KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate TIGRAF_KEY_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    TIGRAF_KEY_SEMICOLON = 51,
    TIGRAF_KEY_APOSTROPHE = 52,
    TIGRAF_KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    TIGRAF_KEY_COMMA = 54,
    TIGRAF_KEY_PERIOD = 55,
    TIGRAF_KEY_SLASH = 56,

    TIGRAF_KEY_CAPSLOCK = 57,

    TIGRAF_KEY_F1 = 58,
    TIGRAF_KEY_F2 = 59,
    TIGRAF_KEY_F3 = 60,
    TIGRAF_KEY_F4 = 61,
    TIGRAF_KEY_F5 = 62,
    TIGRAF_KEY_F6 = 63,
    TIGRAF_KEY_F7 = 64,
    TIGRAF_KEY_F8 = 65,
    TIGRAF_KEY_F9 = 66,
    TIGRAF_KEY_F10 = 67,
    TIGRAF_KEY_F11 = 68,
    TIGRAF_KEY_F12 = 69,

    TIGRAF_KEY_PRINTSCREEN = 70,
    TIGRAF_KEY_SCROLLLOCK = 71,
    TIGRAF_KEY_PAUSE = 72,
    TIGRAF_KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    TIGRAF_KEY_HOME = 74,
    TIGRAF_KEY_PAGEUP = 75,
    TIGRAF_KEY_DELETE = 76,
    TIGRAF_KEY_END = 77,
    TIGRAF_KEY_PAGEDOWN = 78,
    TIGRAF_KEY_RIGHT = 79,
    TIGRAF_KEY_LEFT = 80,
    TIGRAF_KEY_DOWN = 81,
    TIGRAF_KEY_UP = 82,

    TIGRAF_KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    TIGRAF_KEY_KP_DIVIDE = 84,
    TIGRAF_KEY_KP_MULTIPLY = 85,
    TIGRAF_KEY_KP_MINUS = 86,
    TIGRAF_KEY_KP_PLUS = 87,
    TIGRAF_KEY_KP_ENTER = 88,
    TIGRAF_KEY_KP_1 = 89,
    TIGRAF_KEY_KP_2 = 90,
    TIGRAF_KEY_KP_3 = 91,
    TIGRAF_KEY_KP_4 = 92,
    TIGRAF_KEY_KP_5 = 93,
    TIGRAF_KEY_KP_6 = 94,
    TIGRAF_KEY_KP_7 = 95,
    TIGRAF_KEY_KP_8 = 96,
    TIGRAF_KEY_KP_9 = 97,
    TIGRAF_KEY_KP_0 = 98,
    TIGRAF_KEY_KP_PERIOD = 99,

    TIGRAF_KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    TIGRAF_KEY_APPLICATION = 101, /**< windows contextual menu, compose */
    TIGRAF_KEY_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    TIGRAF_KEY_KP_EQUALS = 103,
    TIGRAF_KEY_F13 = 104,
    TIGRAF_KEY_F14 = 105,
    TIGRAF_KEY_F15 = 106,
    TIGRAF_KEY_F16 = 107,
    TIGRAF_KEY_F17 = 108,
    TIGRAF_KEY_F18 = 109,
    TIGRAF_KEY_F19 = 110,
    TIGRAF_KEY_F20 = 111,
    TIGRAF_KEY_F21 = 112,
    TIGRAF_KEY_F22 = 113,
    TIGRAF_KEY_F23 = 114,
    TIGRAF_KEY_F24 = 115,
    TIGRAF_KEY_EXECUTE = 116,
    TIGRAF_KEY_HELP = 117,    /**< AL Integrated Help Center */
    TIGRAF_KEY_MENU = 118,    /**< Menu (show menu) */
    TIGRAF_KEY_SELECT = 119,
    TIGRAF_KEY_STOP = 120,    /**< AC Stop */
    TIGRAF_KEY_AGAIN = 121,   /**< AC Redo/Repeat */
    TIGRAF_KEY_UNDO = 122,    /**< AC Undo */
    TIGRAF_KEY_CUT = 123,     /**< AC Cut */
    TIGRAF_KEY_COPY = 124,    /**< AC Copy */
    TIGRAF_KEY_PASTE = 125,   /**< AC Paste */
    TIGRAF_KEY_FIND = 126,    /**< AC Find */
    TIGRAF_KEY_MUTE = 127,
    TIGRAF_KEY_VOLUMEUP = 128,
    TIGRAF_KEY_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     TIGRAF_KEY_LOCKINGCAPSLOCK = 130,  */
/*     TIGRAF_KEY_LOCKINGNUMLOCK = 131, */
/*     TIGRAF_KEY_LOCKINGSCROLLLOCK = 132, */
    TIGRAF_KEY_KP_COMMA = 133,
    TIGRAF_KEY_KP_EQUALSAS400 = 134,

    TIGRAF_KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    TIGRAF_KEY_INTERNATIONAL2 = 136,
    TIGRAF_KEY_INTERNATIONAL3 = 137, /**< Yen */
    TIGRAF_KEY_INTERNATIONAL4 = 138,
    TIGRAF_KEY_INTERNATIONAL5 = 139,
    TIGRAF_KEY_INTERNATIONAL6 = 140,
    TIGRAF_KEY_INTERNATIONAL7 = 141,
    TIGRAF_KEY_INTERNATIONAL8 = 142,
    TIGRAF_KEY_INTERNATIONAL9 = 143,
    TIGRAF_KEY_LANG1 = 144, /**< Hangul/English toggle */
    TIGRAF_KEY_LANG2 = 145, /**< Hanja conversion */
    TIGRAF_KEY_LANG3 = 146, /**< Katakana */
    TIGRAF_KEY_LANG4 = 147, /**< Hiragana */
    TIGRAF_KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
    TIGRAF_KEY_LANG6 = 149, /**< reserved */
    TIGRAF_KEY_LANG7 = 150, /**< reserved */
    TIGRAF_KEY_LANG8 = 151, /**< reserved */
    TIGRAF_KEY_LANG9 = 152, /**< reserved */

    TIGRAF_KEY_ALTERASE = 153,    /**< Erase-Eaze */
    TIGRAF_KEY_SYSREQ = 154,
    TIGRAF_KEY_CANCEL = 155,      /**< AC Cancel */
    TIGRAF_KEY_CLEAR = 156,
    TIGRAF_KEY_PRIOR = 157,
    TIGRAF_KEY_RETURN2 = 158,
    TIGRAF_KEY_SEPARATOR = 159,
    TIGRAF_KEY_OUT = 160,
    TIGRAF_KEY_OPER = 161,
    TIGRAF_KEY_CLEARAGAIN = 162,
    TIGRAF_KEY_CRSEL = 163,
    TIGRAF_KEY_EXSEL = 164,

    TIGRAF_KEY_KP_00 = 176,
    TIGRAF_KEY_KP_000 = 177,
    TIGRAF_KEY_THOUSANDSSEPARATOR = 178,
    TIGRAF_KEY_DECIMALSEPARATOR = 179,
    TIGRAF_KEY_CURRENCYUNIT = 180,
    TIGRAF_KEY_CURRENCYSUBUNIT = 181,
    TIGRAF_KEY_KP_LEFTPAREN = 182,
    TIGRAF_KEY_KP_RIGHTPAREN = 183,
    TIGRAF_KEY_KP_LEFTBRACE = 184,
    TIGRAF_KEY_KP_RIGHTBRACE = 185,
    TIGRAF_KEY_KP_TAB = 186,
    TIGRAF_KEY_KP_BACKSPACE = 187,
    TIGRAF_KEY_KP_A = 188,
    TIGRAF_KEY_KP_B = 189,
    TIGRAF_KEY_KP_C = 190,
    TIGRAF_KEY_KP_D = 191,
    TIGRAF_KEY_KP_E = 192,
    TIGRAF_KEY_KP_F = 193,
    TIGRAF_KEY_KP_XOR = 194,
    TIGRAF_KEY_KP_POWER = 195,
    TIGRAF_KEY_KP_PERCENT = 196,
    TIGRAF_KEY_KP_LESS = 197,
    TIGRAF_KEY_KP_GREATER = 198,
    TIGRAF_KEY_KP_AMPERSAND = 199,
    TIGRAF_KEY_KP_DBLAMPERSAND = 200,
    TIGRAF_KEY_KP_VERTICALBAR = 201,
    TIGRAF_KEY_KP_DBLVERTICALBAR = 202,
    TIGRAF_KEY_KP_COLON = 203,
    TIGRAF_KEY_KP_HASH = 204,
    TIGRAF_KEY_KP_SPACE = 205,
    TIGRAF_KEY_KP_AT = 206,
    TIGRAF_KEY_KP_EXCLAM = 207,
    TIGRAF_KEY_KP_MEMSTORE = 208,
    TIGRAF_KEY_KP_MEMRECALL = 209,
    TIGRAF_KEY_KP_MEMCLEAR = 210,
    TIGRAF_KEY_KP_MEMADD = 211,
    TIGRAF_KEY_KP_MEMSUBTRACT = 212,
    TIGRAF_KEY_KP_MEMMULTIPLY = 213,
    TIGRAF_KEY_KP_MEMDIVIDE = 214,
    TIGRAF_KEY_KP_PLUSMINUS = 215,
    TIGRAF_KEY_KP_CLEAR = 216,
    TIGRAF_KEY_KP_CLEARENTRY = 217,
    TIGRAF_KEY_KP_BINARY = 218,
    TIGRAF_KEY_KP_OCTAL = 219,
    TIGRAF_KEY_KP_DECIMAL = 220,
    TIGRAF_KEY_KP_HEXADECIMAL = 221,

    TIGRAF_KEY_LCTRL = 224,
    TIGRAF_KEY_LSHIFT = 225,
    TIGRAF_KEY_LALT = 226, /**< alt, option */
    TIGRAF_KEY_LGUI = 227, /**< windows, command (apple), meta */
    TIGRAF_KEY_RCTRL = 228,
    TIGRAF_KEY_RSHIFT = 229,
    TIGRAF_KEY_RALT = 230, /**< alt gr, option */
    TIGRAF_KEY_RGUI = 231, /**< windows, command (apple), meta */

    TIGRAF_KEY_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special SDL_KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     *  See https://usb.org/sites/default/files/hut1_2.pdf
     *
     *  There are way more keys in the spec than we can represent in the
     *  current scancode range, so pick the ones that commonly come up in
     *  real world usage.
     */
    /* @{ */

    TIGRAF_KEY_AUDIONEXT = 258,
    TIGRAF_KEY_AUDIOPREV = 259,
    TIGRAF_KEY_AUDIOSTOP = 260,
    TIGRAF_KEY_AUDIOPLAY = 261,
    TIGRAF_KEY_AUDIOMUTE = 262,
    TIGRAF_KEY_MEDIASELECT = 263,
    TIGRAF_KEY_WWW = 264,             /**< AL Internet Browser */
    TIGRAF_KEY_MAIL = 265,
    TIGRAF_KEY_CALCULATOR = 266,      /**< AL Calculator */
    TIGRAF_KEY_COMPUTER = 267,
    TIGRAF_KEY_AC_SEARCH = 268,       /**< AC Search */
    TIGRAF_KEY_AC_HOME = 269,         /**< AC Home */
    TIGRAF_KEY_AC_BACK = 270,         /**< AC Back */
    TIGRAF_KEY_AC_FORWARD = 271,      /**< AC Forward */
    TIGRAF_KEY_AC_STOP = 272,         /**< AC Stop */
    TIGRAF_KEY_AC_REFRESH = 273,      /**< AC Refresh */
    TIGRAF_KEY_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    TIGRAF_KEY_BRIGHTNESSDOWN = 275,
    TIGRAF_KEY_BRIGHTNESSUP = 276,
    TIGRAF_KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    TIGRAF_KEY_KBDILLUMTOGGLE = 278,
    TIGRAF_KEY_KBDILLUMDOWN = 279,
    TIGRAF_KEY_KBDILLUMUP = 280,
    TIGRAF_KEY_EJECT = 281,
    TIGRAF_KEY_SLEEP = 282,           /**< SC System Sleep */

    TIGRAF_KEY_APP1 = 283,
    TIGRAF_KEY_APP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    TIGRAF_KEY_AUDIOREWIND = 285,
    TIGRAF_KEY_AUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
    /* @{ */

    TIGRAF_KEY_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    TIGRAF_KEY_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    TIGRAF_KEY_CALL = 289, /**< Used for accepting phone calls. */
    TIGRAF_KEY_ENDCALL = 290, /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */

} TIGRAF_KEYCODE;


/**
 * Used as a mask when testing buttons in buttonstate.
 *
 * - Button 1:  Left mouse button
 * - Button 2:  Middle mouse button
 * - Button 3:  Right mouse button
 */
#define TIGRAF_MOUSE_BUTTON(X)       (1 << ((X)-1))
#define TIGRAF_MOUSE_BUTTON_LEFT     TIGRAF_MOUSE_BUTTON(1)
#define TIGRAF_MOUSE_BUTTON_MIDDLE   TIGRAF_MOUSE_BUTTON(2)
#define TIGRAF_MOUSE_BUTTON_RIGHT    TIGRAF_MOUSE_BUTTON(3)
#define TIGRAF_MOUSE_BUTTON_X1       TIGRAF_MOUSE_BUTTON(4)
#define TIGRAF_MOUSE_BUTTON_X2       TIGRAF_MOUSE_BUTTON(5)
