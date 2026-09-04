#include "JISKeyboardHelper.h"

// ESP32BLECombo本体のpress()/release()は次の規則で引数kを解釈する:
//   k < 128        : ASCII文字とみなし、内部asciimap(US配列)でHIDコードへ変換
//   128 <= k < 136 : モディファイアキー。129 = 左Shift
//   k >= 136       : (k - 136) をHID Usage IDとしてそのまま使う（asciimap非経由）
//
// そのため「US配列と位置が異なる記号」を送る場合は、
// 136 + 生HIDコード の形で press()/release() に渡す必要がある。

void JISKeyboardHelper::sendRawKey(uint8_t hidCode, bool shift) {
    if (shift) {
        ble.press(LIB_MOD_LEFT_SHIFT);
    }
    ble.press((uint8_t)(LIB_RAW_OFFSET + hidCode));
    delay(keyDelayMs);
    ble.release((uint8_t)(LIB_RAW_OFFSET + hidCode));
    if (shift) {
        ble.release(LIB_MOD_LEFT_SHIFT);
    }
    delay(keyDelayMs);
}

bool JISKeyboardHelper::printChar(char c) {
    // 英数字・スペースはUS/JISで位置が同じなので、本体のASCII変換(asciimap)にそのまま任せる
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ') {
        ble.write((uint8_t)c);
        delay(keyDelayMs);
        return true;
    }

    // JIS配列で位置がズレる記号のみ、生HIDコードで個別対応する
    uint8_t code = 0;
    bool shift = false;
    bool found = true;

    switch (c) {
        case '!': code = 0x1E; shift = true;  break; // Shift+1
        case '"': code = 0x1F; shift = true;  break; // JIS: Shift+2 = "
        case '#': code = 0x20; shift = true;  break; // Shift+3
        case '$': code = 0x21; shift = true;  break; // Shift+4
        case '%': code = 0x22; shift = true;  break; // Shift+5
        case '&': code = 0x23; shift = true;  break; // Shift+6
        case '\'':code = 0x24; shift = true;  break; // JIS: Shift+7 = '
        case '(': code = 0x25; shift = true;  break; // Shift+8
        case ')': code = 0x26; shift = true;  break; // Shift+9

        case '-': code = 0x2D; shift = false; break;
        case '=': code = 0x2D; shift = true;  break; // JIS: Shift+- = =
        case '^': code = 0x2E; shift = false; break; // JIS専用位置
        case '~': code = 0x2E; shift = true;  break;
        case '@': code = 0x2F; shift = false; break; // JIS: @キー(US "["の位置)
        case '`': code = 0x2F; shift = true;  break;
        case '[': code = 0x30; shift = false; break; // JIS: [キー(US "]"の位置)
        case '{': code = 0x30; shift = true;  break;
        case ']': code = 0x31; shift = false; break; // JIS: ]キー(US "\"の位置)
        case '}': code = 0x31; shift = true;  break;
        case ';': code = 0x33; shift = false; break;
        case '+': code = 0x33; shift = true;  break; // JIS: Shift+; = +
        case ':': code = 0x34; shift = false; break; // JIS: :キー(US "'"の位置)
        case '*': code = 0x34; shift = true;  break;
        case ',': code = 0x36; shift = false; break;
        case '<': code = 0x36; shift = true;  break;
        case '.': code = 0x37; shift = false; break;
        case '>': code = 0x37; shift = true;  break;
        case '/': code = 0x38; shift = false; break;
        case '?': code = 0x38; shift = true;  break;
        case '\\':code = 0x87; shift = false; break; // JIS専用キー(ろ/バックスラッシュ)
        case '_': code = 0x87; shift = true;  break;

        default:
            found = false;
            break;
    }

    if (!found) {
        return false;
    }

    sendRawKey(code, shift);
    return true;
}

void JISKeyboardHelper::print(const char* str) {
    if (str == nullptr) return;
    for (size_t i = 0; str[i] != '\0'; i++) {
        printChar(str[i]);
    }
}

void JISKeyboardHelper::print(const String& str) {
    print(str.c_str());
}

void JISKeyboardHelper::sendEnter() {
    sendRawKey(HID_ENTER, false);
}

void JISKeyboardHelper::sendBackspace() {
    sendRawKey(HID_BACKSPACE, false);
}
