# dp

## 概要
DPマッチングによる音声認識を行うコードです。<br>
言語はC言語です。<br>
認識工学の課題のために作ったものであり、汎用性はありません。

## 動作確認済み環境
wsl2<br>
Ubuntu 20.04<br>
gcc 9.4<br>
(cmake 3.16)

## 使用方法
### ビルド
cmakeがインストールされている場合は
```bash
cmake -S . -B build
cmake --build build
```
されていない場合は
```bash
bash build.bash
```
### 実行
```bash
build/src/main.out <テンプレートデータのディレクトリ> <未知データのディレクトリ> <斜め重み>
```

### 実行例（一部抜粋）
```
00 O CHOOFU CHOOFU
01 O YOTSUYA YOTSUYA
02 X PYUUMA HYUUGA
03 O ZENTSUUJI ZENTSUUJI
```

## 補足
### dp_sym.bashについて
斜め重みを変えた際の認識精度の変化を見るためのbashです。<br>
```bash
bash dp_sym.bash <テンプレートデータのディレクトリ> <未知データのディレクトリ> <斜め重みの開始値> <増分> <終了値>
```
結果はdata/dp_sym_result.txtに（上書きで）保存されます。<br>
各行には各重みに対して正しく認識できた回数が書かれています。<br>
例です。
```txt:data/dp_sym_result.txt
5
19
55
69
78
```

## ライセンス
MITライセンスです。<br>
[LICENSE](./LICENSE "./LICENSE")をお読みください。

## 参考
23年度の認識工学の授業
