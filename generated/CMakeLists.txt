#
# CMakeLists.txt生成用Jinja2テンプレート
#
# 本テンプレートはPython製コードジェネレータから利用され、
# 設定情報を基にCMakeLists.txtを自動生成する。
#
# CommunicationDemo
#   → プロジェクト名
#
# 例)
#
# application.name = CommunicationDemo
#
# ↓生成後
#
# project(
#     CommunicationDemo
#     VERSION 1.0.0
#     LANGUAGES CXX
# )
#
# のようなCMakeファイルが生成される。
#
# 開発者は通信設定やアプリケーション設定のみを定義し、
# ビルド設定は自動生成されたCMakeLists.txtを利用する。
#

# 使用するCMakeの最低バージョン
cmake_minimum_required(VERSION 3.16)

# プロジェクト情報定義
#
# project名は設定ファイルから生成
# AUTOSAR設定やARXMLの情報に応じて
# プロジェクトを切り替え可能
#
project(
    CommunicationDemo
    VERSION 1.0.0
    LANGUAGES CXX
)

# C++17を利用
set(CMAKE_CXX_STANDARD 17)

# C++17対応を必須化
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Senderアプリケーション生成
#
# 生成される実行ファイル:
#   sender
#
# 構成:
#   Sender.cpp      : UDP送信処理
#   SenderMain.cpp  : エントリポイント(main)
#
add_executable(
    sender
    src/Sender.cpp
    src/SenderMain.cpp
)

#
# Sender向けヘッダ検索パス
#
# include配下のヘッダを自動参照
#
target_include_directories(
    sender
    PRIVATE
        include
)

#
# Receiverアプリケーション生成
#
# 生成される実行ファイル:
#   receiver
#
# 構成:
#   Receiver.cpp      : UDP受信処理
#   ReceiverMain.cpp  : エントリポイント(main)
#
add_executable(
    receiver
    src/Receiver.cpp
    src/ReceiverMain.cpp
)

#
# Receiver向けヘッダ検索パス
#
target_include_directories(
    receiver
    PRIVATE
        include
)