/* JNativeHook: Global keyboard and mouse listeners for Java.
 * Copyright (C) 2006-2021 Alexander Barker.  All Rights Reserved.
 * https://github.com/kwhat/jnativehook/
 *
 * JNativeHook is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JNativeHook is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <jni.h>
#include <uiohook.h>

#include "jni_Converter.h"
#include "com_github_kwhat_jnativehook_NativeInputEvent.h"
#include "com_github_kwhat_jnativehook_keyboard_NativeKeyEvent.h"
#include "com_github_kwhat_jnativehook_mouse_NativeMouseEvent.h"
#include "com_github_kwhat_jnativehook_mouse_NativeMouseWheelEvent.h"


jint jni_ConvertToJavaType(event_type nativeType, jint *javaType) {
    jint status = JNI_ERR;

    if (javaType != NULL) {
        switch (nativeType) {
            case EVENT_KEY_TYPED:
            case EVENT_KEY_PRESSED:
            case EVENT_KEY_RELEASED:
                // 3 = EVENT_HOOK_ENABLED + EVENT_HOOK_DISABLED + UNDEFINED.
                *javaType = com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_FIRST + (nativeType - 3);
                status = JNI_OK;
                break;

            case EVENT_MOUSE_CLICKED:
            case EVENT_MOUSE_PRESSED:
            case EVENT_MOUSE_RELEASED:
            case EVENT_MOUSE_MOVED:
            case EVENT_MOUSE_DRAGGED:
            case EVENT_MOUSE_WHEEL:
                // 6 = (NATIVE_KEY_LAST - NATIVE_KEY_FIRST) + EVENT_HOOK_ENABLED + EVENT_HOOK_DISABLED + UNDEFINED.
                *javaType = com_github_kwhat_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_FIRST + (nativeType - 6);
                status = JNI_OK;
                break;

            default:
                *javaType = 0;
                break;
        }
    }

    return status;
}


jint jni_ConvertToNativeType(jint javaType, event_type *nativeType) {
    jint status = JNI_ERR;

    if (nativeType != NULL) {
        switch (javaType) {
            case com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_TYPED:
            case com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_PRESSED:
            case com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_RELEASED:
                *nativeType = (javaType + 3) - com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_FIRST;
                status = JNI_OK;
                break;

            case com_github_kwhat_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_CLICKED:
            case com_github_kwhat_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_PRESSED:
            case com_github_kwhat_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_RELEASED:
            case com_github_kwhat_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_MOVED:
            case com_github_kwhat_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_DRAGGED:
            case com_github_kwhat_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_WHEEL:
                *nativeType = (javaType + 6) - com_github_kwhat_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_FIRST;
                status = JNI_OK;
                break;

            default:
                *nativeType = 0;
                break;
        }
    }

    return status;
}

/* Keep the public Java keycodes stable across libuiohook's keycode revision.
 * Location distinguishes keypad and left/right variants in Java. */
#define KEY(native, java, location) { native, com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_##java, com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_LOCATION_##location }
static const struct { uint16_t native; jint java; jint location; } keycodes[] = {
    KEY(VC_ESCAPE, VC_ESCAPE, STANDARD),
    KEY(VC_F1, VC_F1, STANDARD),
    KEY(VC_F2, VC_F2, STANDARD),
    KEY(VC_F3, VC_F3, STANDARD),
    KEY(VC_F4, VC_F4, STANDARD),
    KEY(VC_F5, VC_F5, STANDARD),
    KEY(VC_F6, VC_F6, STANDARD),
    KEY(VC_F7, VC_F7, STANDARD),
    KEY(VC_F8, VC_F8, STANDARD),
    KEY(VC_F9, VC_F9, STANDARD),
    KEY(VC_F10, VC_F10, STANDARD),
    KEY(VC_F11, VC_F11, STANDARD),
    KEY(VC_F12, VC_F12, STANDARD),
    KEY(VC_F13, VC_F13, STANDARD),
    KEY(VC_F14, VC_F14, STANDARD),
    KEY(VC_F15, VC_F15, STANDARD),
    KEY(VC_F16, VC_F16, STANDARD),
    KEY(VC_F17, VC_F17, STANDARD),
    KEY(VC_F18, VC_F18, STANDARD),
    KEY(VC_F19, VC_F19, STANDARD),
    KEY(VC_F20, VC_F20, STANDARD),
    KEY(VC_F21, VC_F21, STANDARD),
    KEY(VC_F22, VC_F22, STANDARD),
    KEY(VC_F23, VC_F23, STANDARD),
    KEY(VC_F24, VC_F24, STANDARD),
    KEY(VC_BACKQUOTE, VC_BACKQUOTE, STANDARD),
    KEY(VC_1, VC_1, STANDARD),
    KEY(VC_2, VC_2, STANDARD),
    KEY(VC_3, VC_3, STANDARD),
    KEY(VC_4, VC_4, STANDARD),
    KEY(VC_5, VC_5, STANDARD),
    KEY(VC_6, VC_6, STANDARD),
    KEY(VC_7, VC_7, STANDARD),
    KEY(VC_8, VC_8, STANDARD),
    KEY(VC_9, VC_9, STANDARD),
    KEY(VC_0, VC_0, STANDARD),
    KEY(VC_MINUS, VC_MINUS, STANDARD),
    KEY(VC_EQUALS, VC_EQUALS, STANDARD),
    KEY(VC_BACKSPACE, VC_BACKSPACE, STANDARD),
    KEY(VC_TAB, VC_TAB, STANDARD),
    KEY(VC_CAPS_LOCK, VC_CAPS_LOCK, STANDARD),
    KEY(VC_A, VC_A, STANDARD),
    KEY(VC_B, VC_B, STANDARD),
    KEY(VC_C, VC_C, STANDARD),
    KEY(VC_D, VC_D, STANDARD),
    KEY(VC_E, VC_E, STANDARD),
    KEY(VC_F, VC_F, STANDARD),
    KEY(VC_G, VC_G, STANDARD),
    KEY(VC_H, VC_H, STANDARD),
    KEY(VC_I, VC_I, STANDARD),
    KEY(VC_J, VC_J, STANDARD),
    KEY(VC_K, VC_K, STANDARD),
    KEY(VC_L, VC_L, STANDARD),
    KEY(VC_M, VC_M, STANDARD),
    KEY(VC_N, VC_N, STANDARD),
    KEY(VC_O, VC_O, STANDARD),
    KEY(VC_P, VC_P, STANDARD),
    KEY(VC_Q, VC_Q, STANDARD),
    KEY(VC_R, VC_R, STANDARD),
    KEY(VC_S, VC_S, STANDARD),
    KEY(VC_T, VC_T, STANDARD),
    KEY(VC_U, VC_U, STANDARD),
    KEY(VC_V, VC_V, STANDARD),
    KEY(VC_W, VC_W, STANDARD),
    KEY(VC_X, VC_X, STANDARD),
    KEY(VC_Y, VC_Y, STANDARD),
    KEY(VC_Z, VC_Z, STANDARD),
    KEY(VC_OPEN_BRACKET, VC_OPEN_BRACKET, STANDARD),
    KEY(VC_CLOSE_BRACKET, VC_CLOSE_BRACKET, STANDARD),
    KEY(VC_BACK_SLASH, VC_BACK_SLASH, STANDARD),
    KEY(VC_SEMICOLON, VC_SEMICOLON, STANDARD),
    KEY(VC_QUOTE, VC_QUOTE, STANDARD),
    KEY(VC_ENTER, VC_ENTER, STANDARD),
    KEY(VC_COMMA, VC_COMMA, STANDARD),
    KEY(VC_PERIOD, VC_PERIOD, STANDARD),
    KEY(VC_SLASH, VC_SLASH, STANDARD),
    KEY(VC_SPACE, VC_SPACE, STANDARD),
    KEY(VC_PRINTSCREEN, VC_PRINTSCREEN, STANDARD),
    KEY(VC_SCROLL_LOCK, VC_SCROLL_LOCK, STANDARD),
    KEY(VC_PAUSE, VC_PAUSE, STANDARD),
    KEY(VC_INSERT, VC_INSERT, STANDARD),
    KEY(VC_DELETE, VC_DELETE, STANDARD),
    KEY(VC_HOME, VC_HOME, STANDARD),
    KEY(VC_END, VC_END, STANDARD),
    KEY(VC_PAGE_UP, VC_PAGE_UP, STANDARD),
    KEY(VC_PAGE_DOWN, VC_PAGE_DOWN, STANDARD),
    KEY(VC_UP, VC_UP, STANDARD),
    KEY(VC_LEFT, VC_LEFT, STANDARD),
    KEY(VC_BEGIN, VC_CLEAR, STANDARD),
    KEY(VC_RIGHT, VC_RIGHT, STANDARD),
    KEY(VC_DOWN, VC_DOWN, STANDARD),
    KEY(VC_NUM_LOCK, VC_NUM_LOCK, NUMPAD),
    KEY(VC_KP_DECIMAL, VC_SEPARATOR, NUMPAD),
    KEY(VC_SHIFT_L, VC_SHIFT, LEFT),
    KEY(VC_CONTROL_L, VC_CONTROL, LEFT),
    KEY(VC_ALT_L, VC_ALT, LEFT),
    KEY(VC_META_L, VC_META, LEFT),
    KEY(VC_CONTEXT_MENU, VC_CONTEXT_MENU, STANDARD),
    KEY(VC_POWER, VC_POWER, STANDARD),
    KEY(VC_SLEEP, VC_SLEEP, STANDARD),
    KEY(VC_WAKE, VC_WAKE, STANDARD),
    KEY(VC_MEDIA_PLAY, VC_MEDIA_PLAY, STANDARD),
    KEY(VC_MEDIA_STOP, VC_MEDIA_STOP, STANDARD),
    KEY(VC_MEDIA_PREVIOUS, VC_MEDIA_PREVIOUS, STANDARD),
    KEY(VC_MEDIA_NEXT, VC_MEDIA_NEXT, STANDARD),
    KEY(VC_MEDIA_SELECT, VC_MEDIA_SELECT, STANDARD),
    KEY(VC_MEDIA_EJECT, VC_MEDIA_EJECT, STANDARD),
    KEY(VC_VOLUME_MUTE, VC_VOLUME_MUTE, STANDARD),
    KEY(VC_VOLUME_UP, VC_VOLUME_UP, STANDARD),
    KEY(VC_VOLUME_DOWN, VC_VOLUME_DOWN, STANDARD),
    KEY(VC_APP_MAIL, VC_APP_MAIL, STANDARD),
    KEY(VC_APP_CALCULATOR, VC_APP_CALCULATOR, STANDARD),
    KEY(VC_APP_MUSIC, VC_APP_MUSIC, STANDARD),
    KEY(VC_APP_PICTURES, VC_APP_PICTURES, STANDARD),
    KEY(VC_BROWSER_SEARCH, VC_BROWSER_SEARCH, STANDARD),
    KEY(VC_BROWSER_HOME, VC_BROWSER_HOME, STANDARD),
    KEY(VC_BROWSER_BACK, VC_BROWSER_BACK, STANDARD),
    KEY(VC_BROWSER_FORWARD, VC_BROWSER_FORWARD, STANDARD),
    KEY(VC_BROWSER_STOP, VC_BROWSER_STOP, STANDARD),
    KEY(VC_BROWSER_REFRESH, VC_BROWSER_REFRESH, STANDARD),
    KEY(VC_BROWSER_FAVORITES, VC_BROWSER_FAVORITES, STANDARD),
    KEY(VC_KATAKANA, VC_KATAKANA, STANDARD),
    KEY(VC_UNDERSCORE, VC_UNDERSCORE, STANDARD),
    KEY(VC_KANA, VC_FURIGANA, STANDARD),
    KEY(VC_KANJI, VC_KANJI, STANDARD),
    KEY(VC_HIRAGANA, VC_HIRAGANA, STANDARD),
    KEY(VC_SUN_HELP, VC_SUN_HELP, STANDARD),
    KEY(VC_SUN_STOP, VC_SUN_STOP, STANDARD),
    KEY(VC_SUN_PROPS, VC_SUN_PROPS, STANDARD),
    KEY(VC_SUN_FRONT, VC_SUN_FRONT, STANDARD),
    KEY(VC_SUN_OPEN, VC_SUN_OPEN, STANDARD),
    KEY(VC_SUN_FIND, VC_SUN_FIND, STANDARD),
    KEY(VC_SUN_AGAIN, VC_SUN_AGAIN, STANDARD),
    KEY(VC_SUN_UNDO, VC_SUN_UNDO, STANDARD),
    KEY(VC_SUN_COPY, VC_SUN_COPY, STANDARD),
    KEY(VC_SUN_INSERT, VC_SUN_INSERT, STANDARD),
    KEY(VC_SUN_CUT, VC_SUN_CUT, STANDARD),
    KEY(VC_SHIFT_R, VC_SHIFT, RIGHT),
    KEY(VC_CONTROL_R, VC_CONTROL, RIGHT),
    KEY(VC_ALT_R, VC_ALT, RIGHT),
    KEY(VC_META_R, VC_META, RIGHT),
    KEY(VC_KP_0, VC_0, NUMPAD),
    KEY(VC_KP_1, VC_1, NUMPAD),
    KEY(VC_KP_2, VC_2, NUMPAD),
    KEY(VC_KP_3, VC_3, NUMPAD),
    KEY(VC_KP_4, VC_4, NUMPAD),
    KEY(VC_KP_5, VC_5, NUMPAD),
    KEY(VC_KP_6, VC_6, NUMPAD),
    KEY(VC_KP_7, VC_7, NUMPAD),
    KEY(VC_KP_8, VC_8, NUMPAD),
    KEY(VC_KP_9, VC_9, NUMPAD),
    KEY(VC_KP_ENTER, VC_ENTER, NUMPAD),
    KEY(VC_KP_COMMA, VC_COMMA, NUMPAD),
    KEY(VC_KP_END, VC_END, NUMPAD),
    KEY(VC_KP_DOWN, VC_DOWN, NUMPAD),
    KEY(VC_KP_PAGE_DOWN, VC_PAGE_DOWN, NUMPAD),
    KEY(VC_KP_LEFT, VC_LEFT, NUMPAD),
    KEY(VC_KP_RIGHT, VC_RIGHT, NUMPAD),
    KEY(VC_KP_HOME, VC_HOME, NUMPAD),
    KEY(VC_KP_UP, VC_UP, NUMPAD),
    KEY(VC_KP_PAGE_UP, VC_PAGE_UP, NUMPAD),
    KEY(VC_KP_INSERT, VC_INSERT, NUMPAD),
    KEY(VC_KP_DELETE, VC_DELETE, NUMPAD),
    KEY(VC_KP_MULTIPLY, VC_KP_MULTIPLY, NUMPAD),
    KEY(VC_KP_ADD, VC_KP_ADD, NUMPAD),
    KEY(VC_KP_SUBTRACT, VC_KP_SUBTRACT, NUMPAD),
    KEY(VC_KP_DIVIDE, VC_KP_DIVIDE, NUMPAD),
    KEY(VC_KP_CLEAR, VC_CLEAR, NUMPAD),
    KEY(VC_KP_EQUALS, VC_KP_EQUALS, NUMPAD),
    KEY(VC_KP_SEPARATOR, VC_KP_SEPARATOR, NUMPAD),
};
#undef KEY

jint jni_ConvertToJavaLocation(unsigned short *keycode, jint *location) {
    if (keycode == NULL || location == NULL) return JNI_ERR;
    for (size_t i = 0; i < sizeof(keycodes) / sizeof(keycodes[0]); i++) {
        if (keycodes[i].native == *keycode) {
            *keycode = (uint16_t) keycodes[i].java;
            *location = keycodes[i].location;
            return JNI_OK;
        }
    }
    *keycode = com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_VC_UNDEFINED;
    *location = com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_LOCATION_UNKNOWN;
    return JNI_OK;
}

jint jni_ConvertToNativeKeycode(jint keycode, jint location, uint16_t *native) {
    if (native == NULL) return JNI_ERR;
    for (size_t i = 0; i < sizeof(keycodes) / sizeof(keycodes[0]); i++) {
        if (keycodes[i].java == keycode && (keycodes[i].location == location ||
                (location == com_github_kwhat_jnativehook_keyboard_NativeKeyEvent_LOCATION_UNKNOWN))) {
            *native = keycodes[i].native;
            return JNI_OK;
        }
    }
    *native = VC_UNDEFINED;
    return JNI_ERR;
}
