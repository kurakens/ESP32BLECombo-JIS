# Contributing to ESP32BLECombo-JIS

*(Japanese follows English / 日本語は英語の後に続きます)*

First off, thank you for taking the time to contribute! 🙏 
Whether it's reporting a bug, proposing a new feature, improving documentation, or submitting a code fix, all contributions are greatly appreciated.

Please take a moment to review the following guidelines to help make your contributions effective.

---

## 1. Reporting Issues / Bug Reports

If you encounter a bug, unexpected behavior, or compatibility issues with certain ESP32 boards, please open an Issue.

* **Search Existing Issues:** Check if the issue has already been reported before creating a new one.
* **Provide Reproduction Details:** To help us diagnose the problem quickly, please include:
  * Your ESP32 board model (e.g., ESP32-WROOM-32, ESP32-S3, M5Stack).
  * Arduino core for ESP32 version / ESP-IDF version.
  * A minimal reproducible example (code snippet).
  * Host device OS (Windows, macOS, iOS, Android, Linux, etc.) where Bluetooth pairing or typing failed.

## 2. Suggesting New Features

We welcome ideas and feature requests, especially regarding:
* Additional Japanese JIS keyboard layout mappings or modifier handling.
* Compatibility improvements with new hardware variants or operating systems.
* API enhancements for ease of use.

## 3. Pull Requests (PRs)

Contributions via Pull Requests are very welcome!

* **Fork & Branch:** Fork the repository and create your feature branch from `main` (or `master`).
* **Code Style:** Keep your code clean, well-commented, and consistent with the existing style.
* **Test Before Submitting:** Verify that your changes compile successfully and work correctly on real hardware (ESP32) with Japanese JIS input mode enabled.
* **Description:** Clearly explain what your PR solves or implements in the description box.

---

## コントリビューションガイド（日本語）

まずは **ESP32BLECombo-JIS** プロジェクトにご関心をお持ちいただきありがとうございます！🙏
バグの報告、新機能の提案、ドキュメントの改善、コードの修正など、どのような貢献でも大歓迎です。

スムーズな開発とメンテナンスのため、以下のガイドラインをご一読ください。

---

### 1. バグや不具合の報告 (Issues)

バグや期待通りに動作しない挙動、特定のESP32ボードとの互換性問題などを見つけた場合は、Issueを作成してください。

* **既存のIssueの確認:** 新規作成する前に、同様の問題がすでに報告されていないかご確認ください。
* **環境情報の記載:** 原因特定をスムーズに行うため、以下の情報を可能な限り記載してください。
  * 使用しているESP32ボードの型番（例: ESP32-WROOM-32, ESP32-S3, M5Stack 等）
  * Arduino core for ESP32 のバージョン / ESP-IDF のバージョン
  * 最小限の再現コード（スケッチ）
  * 接続先ホスト端末のOS（Windows, macOS, iOS, Android, Linux 等）

### 2. 新機能の提案 (Feature Requests)

以下のような機能提案やアイデアを歓迎します。
* 日本語JISキーボード配列のマッピング追加や特殊キーの対応強化
* 新しいハードウェアバリエーションやOSとの互換性向上
* APIの使い勝手を改善する提案

### 3. プルリクエスト (Pull Requests)

コードの修正や機能追加のプルリクエストも大歓迎です！

* **ブランチの作成:** リポジトリをフォークし、`main`（または `master`）ブランチから作業用ブランチを作成してください。
* **コードスタイル:** 既存のコードスタイルに合わせ、必要に応じてコメントを残してください。
* **動作確認:** 提出前にコンパイルエラーがないこと、および実機のESP32（日本語JIS環境）で正しく動作することをご確認ください。
* **変更内容の説明:** PRの説明欄に「何を解決・実装するのか」をわかりやすく記載してください。
