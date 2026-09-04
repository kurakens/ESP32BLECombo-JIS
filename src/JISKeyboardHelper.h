/*
 * JISKeyboardHelper
 *
 * ESP32BLEComboJIS の press()/release() インターフェースを利用して、
 * 日本語(JIS)キーボード配列で正しい文字が入力されるように
 * USB HID Usage ID へ変換して送信するアドオンクラスです。
 *
 * 元プロジェクト: ESP32BLECombo by kokodev
 * https://github.com/kokofixcomputers/ESP32BLECombo (MIT License)
 *
 * License: MIT
 */

#pragma once

#include <Arduino.h>
#include "ESP32BLEComboJIS.h"

// ESP32BLEComboJIS::press()/release() の値の扱い（本体ソース解析結果）:
//   k < 128        : ASCII文字として解釈し、内部のasciimapテーブル(US配列前提)でHIDコードに変換する
//   128 <= k < 136 : モディファイアキー。 (k-128)ビット目を立てる。129 = 左Shift
//   k >= 136       : (k - 136) を「生のHID Usage ID」としてそのまま送信する
//
// JIS配列で位置がズレる記号は、asciimap(US配列)を経由させず、
// 136 + 生HIDコード の形で直接送ることで回避する。
#define LIB_MOD_LEFT_SHIFT   129   // 左Shiftモディファイア
#define LIB_RAW_OFFSET       136   // 生HIDコードを送る際のオフセット

// 主要な特殊キーの生HID Usage ID（136を足してpress/releaseに渡す）
#define HID_ENTER        0x28
#define HID_BACKSPACE    0x2A
#define HID_TAB          0x2B

class JISKeyboardHelper {
public:
    // 使い方: JISKeyboardHelper jisKb(ble);  ※ble は ESP32BLEComboJIS のインスタンス
    explicit JISKeyboardHelper(ESP32BLEComboJIS& bleRef) : ble(bleRef) {}

    // 1文字をJIS配列として解釈し、対応するHIDキーを送信する
    // 対応できない文字の場合は false を返す
    bool printChar(char c);

    // 文字列をまとめて送信する（対応できない文字はスキップする）
    void print(const char* str);
    void print(const String& str);

    // Enterキー送信（ログイン画面などでの実行用）
    void sendEnter();

    // Backspaceキー送信
    void sendBackspace();

    // キー送信の間隔（ms）。連続入力で文字抜けする場合は増やす
    void setKeyDelay(uint16_t ms) { keyDelayMs = ms; }

private:
    ESP32BLEComboJIS& ble;
    uint16_t keyDelayMs = 10;

    // 生HIDコード（0x00〜0x7F程度）をJIS想定で送信する。
    // 内部で136を加算し、ライブラリのasciimap変換を経由しないようにする。
    void sendRawKey(uint8_t hidCode, bool shift);
};
