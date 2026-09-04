# ESP32BLECombo-JIS（[kokofixcomputers/ESP32BLECombo](https://github.com/kokofixcomputers/ESP32BLECombo) のフォーク）

このリポジトリは、kokodev氏によるESP32BLEComboライブラリ（MITライセンス）をフォークし、
**日本語(JIS 106/109)キーボード配列**で記号が正しく入力されるようにする
`JISKeyboardHelper` クラスを追加したものです。

## 元プロジェクトとの重要な違い：名前の衝突を回避

このフォークは、クラス名・ファイル名を **すべて `...JIS` サフィックス付きにリネーム** しています
（`ESP32BLECombo` → `ESP32BLEComboJIS` など）。これにより、**元の`ESP32BLECombo`ライブラリと
同時にインストールしても名前が衝突しません**。別プロジェクトで元のライブラリを使っている環境に、
このフォークを追加インストールしても問題なく共存できます。

## JIS配列対応について

`ble.print()` は内部でUS配列前提のASCIIマッピングを使用するため、`@`や`"`などの記号は
JIS配列のOS上では別の文字として入力されます。この問題を回避するため、
`src/JISKeyboardHelper.h` / `.cpp` を追加しました。

```cpp
#include <ESP32BLEComboJIS.h>
#include <JISKeyboardHelper.h>

ESP32BLEComboJIS ble;
JISKeyboardHelper jisKb(ble);

void setup() {
  ESP32BLEComboJISConfig cfg;
  cfg.mode = ESP32BLEComboJISMode::KEYBOARD_MOUSE;
  ble.begin(cfg);
}

void loop() {
  if (ble.isConnected()) {
    jisKb.print("Hello@World!");  // JIS配列で正しく入力される
    jisKb.sendEnter();
  }
}
```

サンプル一式は `examples/JISPasswordKeyboard` を参照してください。
JIS配列非対応の記号を含まない用途であれば、従来どおり本体の`ble.print()`もそのまま使えます。

## 依存ライブラリ

- [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino)（h2zero作）

## ライセンス

MIT License。詳細は [LICENSE](LICENSE) を参照してください。
元プロジェクト（[kokofixcomputers/ESP32BLECombo](https://github.com/kokofixcomputers/ESP32BLECombo)）の著作権は
原作者（kokodev氏）に帰属します。

---

以下は元プロジェクトのREADMEです（クラス名は元のままです。実際に使う際は上記の`...JIS`名を使ってください）。

# ESP32BLECombo

Arduino-style ESP32 BLE HID combo library built on NimBLE-Arduino. It can expose:
- keyboard only
- mouse only
- keyboard + mouse

## Features
- Configurable device name and manufacturer
- Configurable battery level at runtime
- Keyboard appearance, mouse appearance, or generic HID appearance
- Optional static random BLE address override before init
- Keyboard text/key send helpers
- Mouse move, click, press/release, and scroll helpers
- Single class with mode selection

## Notes
- Requires re-pairing after HID report map changes.
- Static address override is optional and platform/core dependent; if the core rejects the address, initialization continues with the default address.
- Appearance affects advertising metadata, but the host primarily determines capabilities from the HID report map.

## Basic use
```cpp
#include <ESP32BLECombo.h>

ESP32BLECombo ble;

void setup() {
  Serial.begin(115200);

  ESP32BLEComboConfig cfg;
  cfg.mode = ESP32BLEComboMode::KEYBOARD_MOUSE;
  cfg.deviceName = "ESP32 Combo";
  cfg.manufacturer = "Espressif";
  cfg.batteryLevel = 87;
  cfg.appearance = ESP32BLEComboAppearance::AUTO;

  ble.begin(cfg);
}

void loop() {
  if (ble.isConnected()) {
    ble.print("hello");
    delay(1000);
  }
}
```


## Typing reliability

Some hosts drop BLE HID key events when reports are sent too quickly. This library now exposes configurable typing delays through `keyPressDelayMs`, `keyReleaseDelayMs`, `keyIntervalDelayMs`, and the runtime setters `setKeyPressDelay`, `setKeyReleaseDelay`, and `setKeyIntervalDelay`.


## Gamepad support

The library now supports `ESP32BLEComboMode::GAMEPAD_ONLY` with a generic BLE HID gamepad report containing 16 buttons, four 16-bit axes (`x`, `y`, `z`, `rz`), and one hat switch. Use `gamepadPress`, `gamepadRelease`, `gamepadSetButtons`, `gamepadSetAxes`, and `gamepadSetHat`.


## Combined keyboard, mouse, and gamepad

Use `ESP32BLEComboMode::KEYBOARD_MOUSE_GAMEPAD` to expose all three HID functions at once through separate report IDs in one HID report descriptor. Re-pair the device after changing modes so the host reloads the descriptor.


## Xbox-style gamepad layout

Set `cfg.gamepadLayout = ESP32BLEGamepadLayout::XBOX_STYLE;` to expose a gamepad report shaped for the browser and app standard gamepad mapping expectation: buttons 0-3 align to A/B/X/Y order, the main axes are left stick on `x/y` and right stick on `z/rz`, and the hat switch remains the D-pad. This is still generic BLE HID, not true XInput, but it improves odds that gamepad tester sites render an Xbox-like preview when the host/browser applies standard mapping.
