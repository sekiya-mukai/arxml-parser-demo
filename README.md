<!-- AUTOSAR Adaptive Platform開発の経験を活かし、YAMLからARXMLおよび送受信アプリを自動生成するツールを作成しました。 PythonとJinja2を利用してコード生成を行い、生成されたアプリはUDP通信による疎通確認が可能です。 送信データは1Byteカウンタで、0〜255を循環送信する仕様です。 -->


app.yaml
    ↓
generate.py
    ↓
Jinja2 Template
    ↓
+------------------+
|  Communication   |
|     .arxml       |
+------------------+
         ↓
+------------------+
| Sender App       |
+------------------+
         ↓
 UDP/TCP
         ↓
+------------------+
| Receiver App     |
+------------------+