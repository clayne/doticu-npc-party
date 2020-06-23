/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Keys {

    using namespace Papyrus;

    enum KEYS
    {
        KEY_INVALID = -1,
        KEY_ESCAPE = 1,
        KEY_1 = 2,
        KEY_2 = 3,
        KEY_3 = 4,
        KEY_4 = 5,
        KEY_5 = 6,
        KEY_6 = 7,
        KEY_7 = 8,
        KEY_8 = 9,
        KEY_9 = 10,
        KEY_0 = 11,
        KEY_MINUS = 12,
        KEY_EQUALS = 13,
        KEY_BACKSPACE = 14,
        KEY_TAB = 15,
        KEY_Q = 16,
        KEY_W = 17,
        KEY_E = 18,
        KEY_R = 19,
        KEY_T = 20,
        KEY_Y = 21,
        KEY_U = 22,
        KEY_I = 23,
        KEY_O = 24,
        KEY_P = 25,
        KEY_LEFT_BRACKET = 26,
        KEY_RIGHT_BRACKET = 27,
        KEY_ENTER = 28,
        KEY_LEFT_CONTROL = 29,
        KEY_A = 30,
        KEY_S = 31,
        KEY_D = 32,
        KEY_F = 33,
        KEY_G = 34,
        KEY_H = 35,
        KEY_J = 36,
        KEY_K = 37,
        KEY_L = 38,
        KEY_SEMICOLON = 39,
        KEY_APOSTROPHE = 40,
        KEY_TILDE = 41,
        KEY_LEFT_SHIFT = 42,
        KEY_BACK_SLASH = 43,
        KEY_Z = 44,
        KEY_X = 45,
        KEY_C = 46,
        KEY_V = 47,
        KEY_B = 48,
        KEY_N = 49,
        KEY_M = 50,
        KEY_COMMA = 51,
        KEY_PERIOD = 52,
        KEY_FORWARD_SLASH = 53,
        KEY_RIGHT_SHIFT = 54,
        KEY_NUM_ASTERISK = 55,
        KEY_LEFT_ALT = 56,
        KEY_SPACEBAR = 57,
        KEY_CAPS_LOCK = 58,
        KEY_F1 = 59,
        KEY_F2 = 60,
        KEY_F3 = 61,
        KEY_F4 = 62,
        KEY_F5 = 63,
        KEY_F6 = 64,
        KEY_F7 = 65,
        KEY_F8 = 66,
        KEY_F9 = 67,
        KEY_F10 = 68,
        KEY_NUM_LOCK = 69,
        KEY_SCROLL_LOCK = 70,
        KEY_NUM_7 = 71,
        KEY_NUM_8 = 72,
        KEY_NUM_9 = 73,
        KEY_NUM_MINUS = 74,
        KEY_NUM_4 = 75,
        KEY_NUM_5 = 76,
        KEY_NUM_6 = 77,
        KEY_NUM_PLUS = 78,
        KEY_NUM_1 = 79,
        KEY_NUM_2 = 80,
        KEY_NUM_3 = 81,
        KEY_NUM_0 = 82,
        KEY_NUM_PERIOD = 83,
        KEY_F11 = 87,
        KEY_F12 = 88,
        KEY_NUM_ENTER = 156,
        KEY_RIGHT_CONTROL = 157,
        KEY_NUM_FORWARD_SLASH = 181,
        KEY_RIGHT_ALT = 184,
        KEY_PAUSE = 197,
        KEY_HOME = 199,
        KEY_UP_ARROW = 200,
        KEY_PAGE_UP = 201,
        KEY_LEFT_ARROW = 203,
        KEY_RIGHT_ARROW = 205,
        KEY_END = 207,
        KEY_DOWN_ARROW = 208,
        KEY_PAGE_DOWN = 209,
        KEY_INSERT = 210,
        KEY_DELETE = 211,
        MOUSE_LEFT = 256,
        MOUSE_RIGHT = 257,
        MOUSE_MIDDLE = 258,
        MOUSE_3 = 259,
        MOUSE_4 = 260,
        MOUSE_5 = 261,
        MOUSE_6 = 262,
        MOUSE_7 = 263,
        MOUSE_WHEEL_UP = 264,
        MOUSE_WHEEL_DOWN = 265,
        PAD_DPAD_UP = 266,
        PAD_DPAD_DOWN = 267,
        PAD_DPAD_LEFT = 268,
        PAD_DPAD_RIGHT = 269,
        PAD_START = 270,
        PAD_BACK = 271,
        PAD_LEFT_THUMB = 272,
        PAD_RIGHT_THUMB = 273,
        PAD_LEFT_SHOULDER = 274,
        PAD_RIGHT_SHOULDER = 275,
        PAD_A = 276,
        PAD_B = 277,
        PAD_X = 278,
        PAD_Y = 279,
        PAD_LEFT_TRIGGER = 280,
        PAD_RIGHT_TRIGGER = 281
    };

    const char* Key_To_String(Int_t key);

    Keys_t* Self();
    Int_t Default_Value(Keys_t* keys, String_t key);
    Int_t Current_Value(Keys_t* keys, String_t key);
    Vector_t<Int_t> Default_Mods(Keys_t* keys, String_t key);
    Vector_t<Int_t> Current_Mods(Keys_t* keys, String_t key);
    String_t Default_Mods_To_String(Keys_t* keys, String_t key);
    String_t Current_Mods_To_String(Keys_t* keys, String_t key);
    String_t Conflicting_Key(Keys_t* keys, String_t key, Int_t value, Int_t mod_1 = -1, Int_t mod_2 = -1, Int_t mod_3 = -1);

}}

namespace doticu_npcp { namespace Keys { namespace Exports {

    bool Register(Registry_t* registry);

}}}
