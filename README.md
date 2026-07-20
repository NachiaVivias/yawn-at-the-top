# yawn at the top

> [いつか、高いところであくびをしましょう。](https://youtu.be/I0GuKxzBy40?t=44)

[![Actions Status](https://github.com/NachiaVivias/yawn-at-the-top/actions/workflows/verify.yml/badge.svg)](https://github.com/NachiaVivias/yawn-at-the-top/actions)

[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://NachiaVivias.github.io/yawn-at-the-top)

`src/` 及び `src-doc/` 下にには、 `notebook.pdf` の出力される可能性があるファイルを配置すること。
実際に出力するかどうかはファイルごとに設定できる。

`test/` 下には、自動テストの対象となるファイルを配置すること。

## フレームワーク [tatyam-prime/ICPC_notebook](https://github.com/tatyam-prime/ICPC_notebook)

### 事前にインストールするもの

- node.js (v18 以上)
- npm
    - `brew install node` / <https://learn.microsoft.com/ja-jp/windows/dev-environment/javascript/nodejs-on-wsl>
- clang-format
    - `brew install clang-format` / `sudo apt install clang-format`
- vivliostyle
    - `npm install -g @vivliostyle/cli`
- その他依存関係
    - `npm install`
- uv
    - https://docs.astral.sh/uv/getting-started/installation/
    - `uv sync --locked`
    - [`competitive-verifier`](https://github.com/competitive-verifier/competitive-verifier) がインストールされる。

### 導入

1. GitHub で新規 private repository を作る。
1. yukicoder の API キーを取得し、 GitHub リポジトリの Settings -> Secrets and variables -> Actions -> New repository secret で Name=`YUKICODER_TOKEN` で登録する。
1.  GitHub リポジトリの Settings -> Actions -> Workflow permissions を Read and Write に設定する。
1. [https://competitive-verifier.github.io/competitive-verifier/installer.ja.html](https://competitive-verifier.github.io/competitive-verifier/installer.ja.html) の手順で Actions のスクリプトを作成し、 `.github/workflows/verify.yml` に保存する。
1. [README.md](README.md) をいい感じに修正する。
1. push する。
1. GitHub の Actions タブを開き、 workflow が動いていることを確認する。


### ライブラリ開発

本システムの設定は、ファイル `build/build_setting.toml` の編集によって行うこと。同ファイルには、設定内容の簡単な説明も書かれている。

コード自動フォーマッタの設定は、ファイル `.clang-format` の編集によって行うこと。

```
make build       # PDF 生成
make verify      # oj-verify
make serve       # oj-verify ページ生成
```

注意すること

* 行幅が大きくなる数式を入れると、ページ末尾にあるはずの行が PDF に出力されなくなる場合がある。
* `.clang-format` で設定した 1 行の文字数制限が PDF の横幅よりも大きいとき、変な改行が入る。
* すべてのライブラリを自動 verify する方針ではない。自動 verify がない機能を編集した後は適切に verify すること。

### 競技での利用

印刷された PDF を目視してプログラムを書き写すことを想定している。

使用したいプログラムを書き写す前に、 `hash_line.sh` を書き写して作成すること。
`hash_line.sh` の標準入力にプログラムを入力することにより、各行の先頭にハッシュ値が追記されたものが出力される。

各行に出力されるハッシュは、ファイルのうちその行までの部分から生成したハッシュである。
したがって、ある行に写し間違いがある場合、その行以降のハッシュのほぼすべてが間違った値になることが期待される。
多くのケースでは、二分探索によって写し間違いがある行を発見できる。ハッシュの計算において空白文字が無視されることに注意すること。
