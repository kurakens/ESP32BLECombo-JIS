/*
 * JISPasswordKeyboard
 *
 * ボタン押下でJIS配列として正しいパスワード文字列 + Enterキーを
 * BLE経由でホストPCに送信するサンプルです。
 *
 * 必要なライブラリ:
 *   - NimBLE-Arduino (h2zero)
 *   - このライブラリ (ESP32BLEComboJIS-JIS)
 *
 * このライブラリは ESP32BLEComboJIS (kokodev作) をベースに、クラス名・
 * ファイル名を ESP32BLEComboJIS にリネームしたフォークです。
 * 元の ESP32BLEComboJIS ライブラリと同時にインストールしても衝突しません。
 */

#include <ESP32BLEComboJIS.h>
#include <JISKeyboardHelper.h>

#define BUTTON_PIN 9
#define PASSWORD "your_password_here"  // 実際のパスワードに書き換える

ESP32BLEComboJIS ble;
JISKeyboardHelper jisKb(ble);

bool lastState = HIGH;

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  ESP32BLEComboJISConfig cfg;
  cfg.mode = ESP32BLEComboJISMode::KEYBOARD_MOUSE;
  cfg.deviceName = "PassKey NanoH2";
  cfg.manufacturer = "M5Stack";
  cfg.batteryLevel = 100;

  ble.begin(cfg);
  jisKb.setKeyDelay(15); // 文字抜けする場合は値を大きくする

  Serial.println("BLE Keyboard ready (JIS mode). Waiting for pairing...");
}

void loop() {
  bool currentState = digitalRead(BUTTON_PIN);

  if (currentState != lastState) {
    delay(30); // チャタリング防止
    currentState = digitalRead(BUTTON_PIN);

    if (currentState == LOW) {
      Serial.println("Button PRESSED");

      if (ble.isConnected()) {
        Serial.println("Sending password (JIS layout)...");
        jisKb.print(PASSWORD);
        delay(100);
        jisKb.sendEnter();
      } else {
        Serial.println("Not connected to BLE host.");
      }
    }
    lastState = currentState;
  }
}
