#pragma once

#define HT_MOUSE_LBUTTON		1
#define HT_MOUSE_RBUTTON		2
#define HT_MOUSE_BUTTON3		3
#define HT_MOUSE_BUTTON4		4
#define HT_MOUSE_BUTTON5		5
#define HT_MOUSE_BUTTON6		6
#define HT_MOUSE_BUTTON7		7
#define HT_MOUSE_BUTTON8		8
#define HT_MOUSE_BUTTON9		9

#define HT_KEY_UNKNOWN			-1

#ifdef HT_WINDOWS

#define HT_KEY_SPACE			32
#define HT_KEY_APOSTROPHE		39 /* ' */
#define HT_KEY_COMMA			44 /* , */
#define HT_KEY_MINUS			45 /* - */
#define HT_KEY_PERIOD			46 /* . */
#define HT_KEY_SLASH			47 /* / */

#define HT_KEY_0				48
#define HT_KEY_1				49
#define HT_KEY_2				50
#define HT_KEY_3				51
#define HT_KEY_4				52
#define HT_KEY_5				53
#define HT_KEY_6				54
#define HT_KEY_7				55
#define HT_KEY_8				56
#define HT_KEY_9				57

#define HT_KEY_SEMICOLON		59 /* ; */
#define HT_KEY_EQUAL			61 /* = */

#define HT_KEY_A				65
#define HT_KEY_B				66
#define HT_KEY_C				67
#define HT_KEY_D				68
#define HT_KEY_E				69
#define HT_KEY_F				70
#define HT_KEY_G				71
#define HT_KEY_H				72
#define HT_KEY_I				73
#define HT_KEY_J				74
#define HT_KEY_K				75
#define HT_KEY_L				76
#define HT_KEY_M				77
#define HT_KEY_N				78
#define HT_KEY_O				79
#define HT_KEY_P				80
#define HT_KEY_Q				81
#define HT_KEY_R				82
#define HT_KEY_S				83
#define HT_KEY_T				84
#define HT_KEY_U				85
#define HT_KEY_V				86
#define HT_KEY_W				87
#define HT_KEY_X				88
#define HT_KEY_Y				89
#define HT_KEY_Z				90

#define HT_KEY_LEFT_BRACKET		91 /* [ */
#define HT_KEY_BACKSLASH		92 /* \ */
#define HT_KEY_RIGHT_BRACKET	93 /* ] */
#define HT_KEY_GRAVE_ACCENT		96 /* ` */

#define HT_KEY_WORLD_1			161 /* non-US #1 */
#define HT_KEY_WORLD_2			162 /* non-US #2 */
#define HT_KEY_ESCAPE			256

#define HT_KEY_ENTER			257
#define HT_KEY_TAB				258
#define HT_KEY_BACKSPACE		259
#define HT_KEY_INSERT			260
#define HT_KEY_DELETE			261
#define HT_KEY_RIGHT			262
#define HT_KEY_LEFT				263
#define HT_KEY_DOWN				264
#define HT_KEY_UP				265
#define HT_KEY_PAGE_UP			266
#define HT_KEY_PAGE_DOWN		267
#define HT_KEY_HOME				268
#define HT_KEY_END				269
#define HT_KEY_CAPS_LOCK		280
#define HT_KEY_SCROLL_LOCK		281
#define HT_KEY_NUM_LOCK			282
#define HT_KEY_PRINT_SCREEN		283
#define HT_KEY_PAUSE			284

#define HT_KEY_F1				290
#define HT_KEY_F2				291
#define HT_KEY_F3				292
#define HT_KEY_F4				293
#define HT_KEY_F5				294
#define HT_KEY_F6				295
#define HT_KEY_F7				296
#define HT_KEY_F8				297
#define HT_KEY_F9				298
#define HT_KEY_F10				299
#define HT_KEY_F11				300
#define HT_KEY_F12				301
#define HT_KEY_F13				302
#define HT_KEY_F14				303
#define HT_KEY_F15				304
#define HT_KEY_F16				305
#define HT_KEY_F17				306
#define HT_KEY_F18				307
#define HT_KEY_F19				308
#define HT_KEY_F20				309
#define HT_KEY_F21				310
#define HT_KEY_F22				311
#define HT_KEY_F23				312
#define HT_KEY_F24				313
#define HT_KEY_F25				314

#define HT_KEY_KP_0				320
#define HT_KEY_KP_1				321
#define HT_KEY_KP_2				322
#define HT_KEY_KP_3				323
#define HT_KEY_KP_4				324
#define HT_KEY_KP_5				325
#define HT_KEY_KP_6				326
#define HT_KEY_KP_7				327
#define HT_KEY_KP_8				328
#define HT_KEY_KP_9				329

#define HT_KEY_KP_DECIMAL		330
#define HT_KEY_KP_DIVIDE		331
#define HT_KEY_KP_MULTIPLY		332
#define HT_KEY_KP_SUBTRACT		333
#define HT_KEY_KP_ADD			334
#define HT_KEY_KP_ENTER			335
#define HT_KEY_KP_EQUAL			336

#define HT_KEY_LEFT_SHIFT		340
#define HT_KEY_LEFT_CONTROL		341
#define HT_KEY_LEFT_ALT			342
#define HT_KEY_LEFT_SUPER		343

#define HT_KEY_RIGHT_SHIFT		344
#define HT_KEY_RIGHT_CONTROL	345
#define HT_KEY_RIGHT_ALT		346
#define HT_KEY_RIGHT_SUPER		347

#define HT_KEY_MENU				348

#elif defined(HT_LINUX)

// Todo: Printscreen keycode

#define HT_KEY_ESCAPE			1

#define HT_KEY_1				2
#define HT_KEY_2				3
#define HT_KEY_3				4
#define HT_KEY_4				5
#define HT_KEY_5				6
#define HT_KEY_6				7
#define HT_KEY_7				8
#define HT_KEY_8				9
#define HT_KEY_9				10
#define HT_KEY_0				11

#define HT_KEY_Q				16
#define HT_KEY_W				17
#define HT_KEY_E				18
#define HT_KEY_R				19
#define HT_KEY_T				20
#define HT_KEY_Y				21
#define HT_KEY_U				22
#define HT_KEY_I				23
#define HT_KEY_O				24
#define HT_KEY_P				25

#define HT_KEY_A				30
#define HT_KEY_S				31
#define HT_KEY_D				32
#define HT_KEY_F				33
#define HT_KEY_G				34
#define HT_KEY_H				35
#define HT_KEY_J				36
#define HT_KEY_K				37
#define HT_KEY_L				38

#define HT_KEY_Z				44
#define HT_KEY_X				45
#define HT_KEY_C				46
#define HT_KEY_V				47
#define HT_KEY_B				48
#define HT_KEY_N				49
#define HT_KEY_M				50

#define HT_KEY_TAB				15
#define HT_KEY_MINUS			12
#define HT_KEY_EQUAL			13
#define HT_KEY_BACKSPACE		14
#define HT_KEY_LEFT_BRACKET		26
#define HT_KEY_RIGHT_BRACKET	27
#define HT_KEY_ENTER			28
#define HT_KEY_LEFT_CTRL		29
#define HT_KEY_SEMICOLON		39
#define HT_KEY_APOSTROPHE		40
#define HT_KEY_GRAVE_ACCENT		41
#define HT_KEY_LEFT_SHIFT		42
#define HT_KEY_BACKSLASH		43

#define HT_KEY_COMMA			51
#define HT_KEY_PERIOD			52
#define HT_KEY_SLASH			53
#define HT_KEY_RIGHT_SHIFT		54
#define HT_KEY_KP_MULTIPLY		55
#define HT_KEY_LEFT_ALT			56
#define HT_KEY_SPACE			57
#define HT_KEY_CAPS_LOCK		58

#define HT_KEY_NUM_LOCK			69
#define HT_KEY_SCROLL_LOCK		70
#define HT_KEY_KP_7				71
#define HT_KEY_KP_8				72
#define HT_KEY_KP_9				73
#define HT_KEY_KP_SUBTRACT		74
#define HT_KEY_KP_4				75
#define HT_KEY_KP_5				76
#define HT_KEY_KP_6				77
#define HT_KEY_KP_ADD			78
#define HT_KEY_KP_1				79
#define HT_KEY_KP_2				80
#define HT_KEY_KP_3				81
#define HT_KEY_KP_0				82
#define HT_KEY_KP_DECIMAL		83

#define HT_KEY_KP_DIVIDE		98
#define HT_KEY_KP_ENTER			96

#define HT_KEY_F1				59
#define HT_KEY_F2				60
#define HT_KEY_F3				61
#define HT_KEY_F4				62
#define HT_KEY_F5				63
#define HT_KEY_F6				64
#define HT_KEY_F7				65
#define HT_KEY_F8				66
#define HT_KEY_F9				67
#define HT_KEY_F10				68
#define HT_KEY_F11				87
#define HT_KEY_F12				88
#define HT_KEY_F13				183
#define HT_KEY_F14				184
#define HT_KEY_F15				185
#define HT_KEY_F16				186
#define HT_KEY_F17				187
#define HT_KEY_F18				188
#define HT_KEY_F19				189
#define HT_KEY_F20				190
#define HT_KEY_F21				191
#define HT_KEY_F22				192
#define HT_KEY_F23				193
#define HT_KEY_F24				194


#define HT_KEY_RIGHT_CTRL		97
#define HT_KEY_RIGHT_ALT		100
#define HT_KEY_LINEFEED			101
#define HT_KEY_HOME				102
#define HT_KEY_UP				103
#define HT_KEY_PAGE_UP			104
#define HT_KEY_LEFT				105
#define HT_KEY_RIGHT			106
#define HT_KEY_END				107
#define HT_KEY_DOWN				108
#define HT_KEY_PAGE_DOWN		109
#define HT_KEY_INSERT			110
#define HT_KEY_DELETE			111
#define HT_KEY_MACRO			112
#define HT_KEY_MUTE				113
#define HT_KEY_VOLUMEDOWN		114
#define HT_KEY_VOLUMEUP			115
#define HT_KEY_POWER			116	/* SC System Power Down */
#define HT_KEY_KP_EQUAL			117
#define HT_KEY_KP_PLUSMINUS		118
#define HT_KEY_PAUSE			119
#define HT_KEY_SCALE			120	

#else
#	error "Keys for other platforms are not implemented."
#endif
