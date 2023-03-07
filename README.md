# 42 cub3d

## 概要

レイキャスティングで実装した初期のFPSゲーム

- 壁で囲まれたマップを自由に移動できる
- 障害物を設置できる
- ゲーム画面をbmpで保存できる
- 設定ファイルでマップや画像などが設定できる
- 2次元のマップ上でプレイヤーの向きの一定範囲に光線を飛ばして、<br>壁にぶつかったときの距離で描写する壁の高さを決定して縦線1本引く

## Demo

![cub3d](https://user-images.githubusercontent.com/50983708/223070480-e60124f3-72a4-4d5d-a790-36bc2d507786.gif)

## Usage

`./cub3d [conf_file]`

- `--save`: 初期位置の画像を`capture.bmp`に保存

## 設定ファイル

- `R`: ウィンドウサイズ
- `C`: 天井の色
- `F`: 床の色
- `NO`,`WE`,`SO`,`EA`: 壁のテクスチャ
- `S`: 障害物のテクスチャ
- マップ
  - `1`: 壁
  - `2`: 障害物
  - `N`,`W`,`S`,`E`: プレイヤーの位置と向き

```txt
R 822 620
C 0,0,238
F 221,221,221

NO ./textures/eagle.xpm
SO ./textures/colorstone.xpm
WE ./textures/greystone.xpm
EA ./textures/purplestone.xpm

S ./textures/barrel.xpm

1111111111  1111111
1220000221  102000W1
12200002211110220001
12200002200000200001
12200002200000000001
12200000000000011111
12200000000000011111
10000000000000000001
10000002222222222221
11111111111111111111

```

## キーワード

`C`,`レイキャスティング`,`ベクトル`,`内積`,`bmp`
