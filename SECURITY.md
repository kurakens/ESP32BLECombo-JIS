# Security Policy / セキュリティポリシー

*(Japanese follows English / 日本語は英語の後に続きます)*

## Supported Versions

Currently, the latest version on the `main` (or `master`) branch and the latest official release are supported with security updates.

| Version | Supported          |
| ------- | ------------------ |
| Latest (`main` / latest release) | :white_check_mark: |
| Older versions | :x:                |

## Reporting a Vulnerability

We take the security and reliability of **ESP32BLECombo-JIS** seriously. Because this library operates in embedded C/C++ environments and handles low-level Bluetooth Low Energy (BLE) HID protocols, memory safety and protocol integrity are important.

If you discover a security vulnerability, **please do not report it via a public GitHub Issue.** Instead, please report it privately using one of the following methods:

1. **GitHub Private Vulnerability Reporting (Preferred):**
   Navigate to the [Security tab](https://github.com/kurakens/ESP32BLECombo-JIS/security) of this repository and click **"Report a vulnerability"** to open a private advisory.
2. **Direct Contact:**
   If private reporting is unavailable, please contact the maintainer directly via GitHub profile links or discussions without disclosing exploit details publicly.

### What to Include in Your Report
To help us triage and resolve the issue quickly, please include:
* A clear description of the vulnerability and its potential impact.
* Steps to reproduce the issue (sample sketch/code, key sequence, or BLE payload).
* Target environment details (ESP32 board model, Arduino core / ESP-IDF version, OS of the host device).
* Any suggested fixes or mitigations, if available.

### Scope & Areas of Interest
We are particularly interested in reports regarding:
* Buffer overflows, memory leaks, or pointer-related vulnerabilities in C/C++ code.
* Malformed BLE HID report handling or unexpected crashes/reboots.
* BLE pairing, bonding, or unauthorized input injection issues specific to this library's implementation.

*(Note: Vulnerabilities inherent to the underlying ESP-IDF, Arduino core for ESP32, or the Bluetooth specification itself should be reported upstream to Espressif or the respective maintainers.)*

---

## セキュリティポリシー（日本語）

### サポート対象バージョン

現在、`main`（または `master`）ブランチの最新コミットおよび最新のリリースバージョンをセキュリティアップデートの対象としています。

| バージョン | サポート状況 |
| ------- | ------------------ |
| 最新版 (`main` / 最新リリース) | :white_check_mark: |
| 過去のバージョン | :x:                |

### 脆弱性の報告方法

**ESP32BLECombo-JIS** は組み込みC/C++環境で動作し、BLE（Bluetooth Low Energy）HIDプロトコルを扱うため、メモリ安全性と動作の信頼性を重視しています。

セキュリティ上の脆弱性を発見された場合は、**公開のGitHub Issueには書き込まず**、以下の手順で非公開にてご報告ください。

1. **GitHub Private Vulnerability Reporting（推奨）:**
   本リポジトリの [Securityタブ](https://github.com/kurakens/ESP32BLECombo-JIS/security) に移動し、**「Report a vulnerability」** から非公開レポートを作成してください。
2. **直接の連絡:**
   上記機能が利用できない場合は、攻撃コード等の詳細を公開せず、メンテナーのGitHubプロフィール等に記載の連絡先へご連絡ください。

### 報告に含めていただきたい内容
迅速な原因特定と修正のため、可能な範囲で以下の情報を含めてください。
* 脆弱性の概要と想定される影響範囲
* 再現手順（最小構成のサンプルスケッチ、キー入力手順、BLEパケットの内容など）
* 動作環境（使用しているESP32ボードの種類、Arduino core / ESP-IDFのバージョン、接続先ホストOSなど）
* （もしあれば）修正案や回避策

### 主な対象範囲（スコープ）
特に以下のような問題に関する報告を歓迎します。
* C/C++コード内のバッファオーバーフロー、メモリリーク、不正なポインタ参照など
* 不正なBLE HIDレポート処理に起因するクラッシュや意図しない再起動
* 本ライブラリの実装に起因するBLEペアリング・ボンディングの不備や意図しないキー入力の問題

※ ESP-IDF自体やArduino core for ESP32、またはBluetooth規格そのものに起因する脆弱性については、Espressif等のアップストリームへご報告ください。
