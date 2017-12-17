#pragma once

#ifdef HT_WINDOWS

#define HT_KEY_UNKNOWN			-1
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
#else
#	error "Keys for other platforms are not implemented."
#endif