/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#pragma once

#define HT_KEY_UNKNOWN         -1

#if defined(HT_WINDOWS)

#define HT_MOUSE_LBUTTON        1
#define HT_MOUSE_RBUTTON        2
#define HT_MOUSE_BUTTON3        3
#define HT_MOUSE_BUTTON4        4
#define HT_MOUSE_BUTTON5        5
#define HT_MOUSE_BUTTON6        6
#define HT_MOUSE_BUTTON7        7
#define HT_MOUSE_BUTTON8        8
#define HT_MOUSE_BUTTON9        9

#define HT_KEY_SPACE            32
#define HT_KEY_APOSTROPHE       39 /* ' */
#define HT_KEY_COMMA            44 /* , */
#define HT_KEY_MINUS            45 /* - */
#define HT_KEY_PERIOD           46 /* . */
#define HT_KEY_SLASH            47 /* / */

#define HT_KEY_0                48
#define HT_KEY_1                49
#define HT_KEY_2                50
#define HT_KEY_3                51
#define HT_KEY_4                52
#define HT_KEY_5                53
#define HT_KEY_6                54
#define HT_KEY_7                55
#define HT_KEY_8                56
#define HT_KEY_9                57

#define HT_KEY_SEMICOLON        59
#define HT_KEY_EQUAL            61

#define HT_KEY_A                65
#define HT_KEY_B                66
#define HT_KEY_C                67
#define HT_KEY_D                68
#define HT_KEY_E                69
#define HT_KEY_F                70
#define HT_KEY_G                71
#define HT_KEY_H                72
#define HT_KEY_I                73
#define HT_KEY_J                74
#define HT_KEY_K                75
#define HT_KEY_L                76
#define HT_KEY_M                77
#define HT_KEY_N                78
#define HT_KEY_O                79
#define HT_KEY_P                80
#define HT_KEY_Q                81
#define HT_KEY_R                82
#define HT_KEY_S                83
#define HT_KEY_T                84
#define HT_KEY_U                85
#define HT_KEY_V                86
#define HT_KEY_W                87
#define HT_KEY_X                88
#define HT_KEY_Y                89
#define HT_KEY_Z                90

#define HT_KEY_LEFT_BRACKET     91
#define HT_KEY_BACKSLASH        92
#define HT_KEY_RIGHT_BRACKET    93
#define HT_KEY_GRAVE_ACCENT     96

#define HT_KEY_WORLD_1          161
#define HT_KEY_WORLD_2          162
#define HT_KEY_ESCAPE           256

#define HT_KEY_ENTER            257
#define HT_KEY_TAB              258
#define HT_KEY_BACKSPACE        259
#define HT_KEY_INSERT           260
#define HT_KEY_DELETE           261
#define HT_KEY_RIGHT            262
#define HT_KEY_LEFT             263
#define HT_KEY_DOWN             264
#define HT_KEY_UP               265
#define HT_KEY_PAGE_UP          266
#define HT_KEY_PAGE_DOWN        267
#define HT_KEY_HOME             268
#define HT_KEY_END              269
#define HT_KEY_CAPS_LOCK        280
#define HT_KEY_SCROLL_LOCK      281
#define HT_KEY_NUM_LOCK         282
#define HT_KEY_PRINT_SCREEN     283
#define HT_KEY_PAUSE            284

#define HT_KEY_F1               290
#define HT_KEY_F2               291
#define HT_KEY_F3               292
#define HT_KEY_F4               293
#define HT_KEY_F5               294
#define HT_KEY_F6               295
#define HT_KEY_F7               296
#define HT_KEY_F8               297
#define HT_KEY_F9               298
#define HT_KEY_F10              299
#define HT_KEY_F11              300
#define HT_KEY_F12              301
#define HT_KEY_F13              302
#define HT_KEY_F14              303
#define HT_KEY_F15              304
#define HT_KEY_F16              305
#define HT_KEY_F17              306
#define HT_KEY_F18              307
#define HT_KEY_F19              308
#define HT_KEY_F20              309
#define HT_KEY_F21              310
#define HT_KEY_F22              311
#define HT_KEY_F23              312
#define HT_KEY_F24              313
#define HT_KEY_F25              314

#define HT_KEY_KP_0             320
#define HT_KEY_KP_1             321
#define HT_KEY_KP_2             322
#define HT_KEY_KP_3             323
#define HT_KEY_KP_4             324
#define HT_KEY_KP_5             325
#define HT_KEY_KP_6             326
#define HT_KEY_KP_7             327
#define HT_KEY_KP_8             328
#define HT_KEY_KP_9             329

#define HT_KEY_KP_DECIMAL       330
#define HT_KEY_KP_DIVIDE        331
#define HT_KEY_KP_MULTIPLY      332
#define HT_KEY_KP_SUBTRACT      333
#define HT_KEY_KP_ADD           334
#define HT_KEY_KP_ENTER         335
#define HT_KEY_KP_EQUAL         336

#define HT_KEY_LEFT_SHIFT       340
#define HT_KEY_LEFT_CONTROL     341
#define HT_KEY_LEFT_ALT         342
#define HT_KEY_LEFT_SUPER       343

#define HT_KEY_RIGHT_SHIFT      344
#define HT_KEY_RIGHT_CONTROL    345
#define HT_KEY_RIGHT_ALT        346
#define HT_KEY_RIGHT_SUPER      347

#define HT_KEY_MENU             348

#elif defined(HT_LINUX)
#include <X11/keysym.h>
// Todo: Printscreen keycode

#define HT_MOUSE_LBUTTON        1
#define HT_MOUSE_BUTTON3        2
#define HT_MOUSE_RBUTTON        3
#define HT_MOUSE_BUTTON4        4
#define HT_MOUSE_BUTTON5        5
#define HT_MOUSE_BUTTON6        6
#define HT_MOUSE_BUTTON7        7
#define HT_MOUSE_BUTTON8        8
#define HT_MOUSE_BUTTON9        9

#define HT_KEY_ESCAPE           XK_Escape

#define HT_KEY_1                XK_1
#define HT_KEY_2                XK_2
#define HT_KEY_3                XK_3
#define HT_KEY_4                XK_4
#define HT_KEY_5                XK_5
#define HT_KEY_6                XK_6
#define HT_KEY_7                XK_7
#define HT_KEY_8                XK_8
#define HT_KEY_9                XK_9
#define HT_KEY_0                XK_0

#define HT_KEY_Q                XK_q
#define HT_KEY_W                XK_w
#define HT_KEY_E                XK_e
#define HT_KEY_R                XK_r
#define HT_KEY_T                XK_t
#define HT_KEY_Y                XK_y
#define HT_KEY_U                XK_u
#define HT_KEY_I                XK_i
#define HT_KEY_O                XK_o
#define HT_KEY_P                XK_p

#define HT_KEY_A                XK_a
#define HT_KEY_S                XK_s
#define HT_KEY_D                XK_d
#define HT_KEY_F                XK_f
#define HT_KEY_G                XK_g
#define HT_KEY_H                XK_h
#define HT_KEY_J                XK_j
#define HT_KEY_K                XK_k
#define HT_KEY_L                XK_l

#define HT_KEY_Z                XK_z
#define HT_KEY_X                XK_x
#define HT_KEY_C                XK_c
#define HT_KEY_V                XK_v
#define HT_KEY_B                XK_b
#define HT_KEY_N                XK_n
#define HT_KEY_M                XK_m

#define HT_KEY_TAB              XK_Tab
#define HT_KEY_MINUS            XK_minus
#define HT_KEY_EQUAL            XK_equal
#define HT_KEY_BACKSPACE        XK_backspace
#define HT_KEY_LEFT_BRACKET     XK_parenleft
#define HT_KEY_RIGHT_BRACKET    XK_parenright
#define HT_KEY_ENTER            XK_Return
#define HT_KEY_SEMICOLON        XK_semicolon
#define HT_KEY_APOSTROPHE       XK_apostrophe
#define HT_KEY_GRAVE_ACCENT     XK_grave
#define HT_KEY_LEFT_SHIFT       XK_Shift_L
#define HT_KEY_RIGHT_SHIFT      XK_Shift_R
#define HT_KEY_BACKSLASH        XK_backslash

#define HT_KEY_COMMA            XK_comma
#define HT_KEY_PERIOD           XK_period
#define HT_KEY_SLASH            XK_slash
#define HT_KEY_KP_MULTIPLY      XK_KP_Multiply
#define HT_KEY_SPACE            XK_space
#define HT_KEY_CAPS_LOCK        XK_Caps_Lock

#define HT_KEY_NUM_LOCK         XK_Num_Lock
#define HT_KEY_SCROLL_LOCK      XK_Scroll_Lock

#define HT_KEY_KP_SUBTRACT      XK_KP_Subtract
#define HT_KEY_KP_ADD           XK_KP_Add
#define HT_KEY_KP_DECIMAL       XK_KP_Decimal
#define HT_KEY_KP_DIVIDE        XK_KP_Divide
#define HT_KEY_KP_ENTER         XK_KP_Enter
#define HT_KEY_KP_EQUAL         XK_KP_Equal

#define HT_KEY_KP_0             XK_KP_0
#define HT_KEY_KP_1             XK_KP_1
#define HT_KEY_KP_2             XK_KP_2
#define HT_KEY_KP_3             XK_KP_3
#define HT_KEY_KP_4             XK_KP_4
#define HT_KEY_KP_5             XK_KP_5
#define HT_KEY_KP_6             XK_KP_6
#define HT_KEY_KP_7             XK_KP_7
#define HT_KEY_KP_8             XK_KP_8
#define HT_KEY_KP_9             XK_KP_9

#define HT_KEY_F1               XK_F1 
#define HT_KEY_F2               XK_F2 
#define HT_KEY_F3               XK_F3 
#define HT_KEY_F4               XK_F4 
#define HT_KEY_F5               XK_F5 
#define HT_KEY_F6               XK_F6 
#define HT_KEY_F7               XK_F7 
#define HT_KEY_F8               XK_F8 
#define HT_KEY_F9               XK_F9 
#define HT_KEY_F10              XK_F10
#define HT_KEY_F11              XK_F11
#define HT_KEY_F12              XK_F12
#define HT_KEY_F13              XK_F13
#define HT_KEY_F14              XK_F14
#define HT_KEY_F15              XK_F15
#define HT_KEY_F16              XK_F16
#define HT_KEY_F17              XK_F17
#define HT_KEY_F18              XK_F18
#define HT_KEY_F19              XK_F19
#define HT_KEY_F20              XK_F20
#define HT_KEY_F21              XK_F21
#define HT_KEY_F22              XK_F22
#define HT_KEY_F23              XK_F23
#define HT_KEY_F24              XK_F24


#define HT_KEY_LEFT_CTRL        XK_Control_L
#define HT_KEY_LEFT_ALT         XK_Alt_L
#define HT_KEY_RIGHT_CTRL       XK_Control_R
#define HT_KEY_RIGHT_ALT        XK_Alt_R

#define HT_KEY_LINEFEED         XK_Linefeed
#define HT_KEY_HOME             XK_Home
#define HT_KEY_LEFT             XK_Left
#define HT_KEY_UP               XK_Up
#define HT_KEY_RIGHT            XK_Right
#define HT_KEY_DOWN             XK_Down


#define HT_KEY_PAGE_UP          XK_Page_Up
#define HT_KEY_END              XK_End
#define HT_KEY_PAGE_DOWN        XK_Page_Down
#define HT_KEY_INSERT           XK_Insert
#define HT_KEY_DELETE           XK_Delete

#define HT_KEY_PAUSE            XK_Pause

#endif // HT_WINDOWS