/*
    Receiverアプリケーション生成用テンプレート

    本ファイルはJinja2テンプレートとして管理されており、
    Python製コードジェネレータによって
    実際のReceiverソースコードへ変換される。

    Receiver
        → クラス名・ファイル名として利用

    50001
        → UDP受信ポート番号として利用

    例)

    app_name = Receiver
    port     = 50001

    ↓生成結果

    #include "Receiver.hpp"

    void Receiver::run()
    {
        ...
    }

    のようなC++コードが生成される。
*/

#include "Receiver.hpp"

#include <arpa/inet.h>

#include <cstdint>
#include <iostream>

void Receiver::run()
{
    // UDP通信用ソケット生成
    //
    // AF_INET   : IPv4
    // SOCK_DGRAM: UDP通信
    int sock =
        socket(
            AF_INET,
            SOCK_DGRAM,
            0);

    // 受信先情報構造体
    sockaddr_in receiverAddr {};

    // IPv4通信を利用
    receiverAddr.sin_family = AF_INET;

    /*
        待受ポート番号設定

        テンプレート変数で指定されたポート番号が
        自動で埋め込まれる。

        例)
        50001
        50002
        60000

        通信設定変更時でも、
        ARXMLや設定ファイルを書き換えるだけで
        コード生成可能。
    */
    receiverAddr.sin_port =
        htons(
            50001
        );

    /*
        INADDR_ANY

        自端末の全てのネットワークインターフェースから
        パケット受信を許可する。

        特定IPに依存しないため、
        開発環境変更時の修正を減らせる。
    */
    receiverAddr.sin_addr.s_addr =
        INADDR_ANY;

    /*
        ソケットとポートを関連付ける。

        bind後は指定ポートで
        受信待ち状態となる。
    */
    bind(
        sock,
        reinterpret_cast<sockaddr*>(
            &receiverAddr),
        sizeof(receiverAddr));

    // 受信データ格納変数
    uint8_t data {};

    // 常時受信ループ
    while(true)
    {
        /*
            UDPデータ受信

            Senderアプリケーションから送信された
            カウンタ値などのデータを取得する。

            本サンプルでは1byteデータを受信。
        */
        recv(
            sock,
            &data,
            sizeof(data),
            0);

        // 受信結果をログ表示
        std::cout
            << "[RX] "
            << static_cast<int>(data)
            << std::endl;
    }
}