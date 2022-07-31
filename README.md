# Videction Lora Communicate Module

Videction（来場者検出システム = Visitor Detection）における通信モジュール部分に関してのリポジトリです。  
Videction は BLE ビーコンを用いた来場者自動検知を行い、その情報を LoRaWAN を用いてサーバへと送信、及び Web アプリケーションでの可視化を行うシステムです。  
その中で本リポジトリは LoRaWAN 機構におけるエンドデバイスの LoRa 通信を用いた通信モジュール部分の実装です。

## 使用デバイス

- MKRWAN1310

## 使い方

- arduino_secrets.h に LoRaWAN サーバから取得した APPEUI と APP_KEY を定義します
- MKRWAN へ書き込みます

## 使用ライブラリ

- MKRWAN_V2
  - version:1.3.2

## 既知のバグ・問題点

issue に記載する
