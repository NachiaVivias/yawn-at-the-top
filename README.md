# yawn at the top

> [いつか、高いところであくびをしましょう。](https://youtu.be/I0GuKxzBy40?t=44)

[![Actions Status](https://github.com/NachiaVivias/yawn-at-the-top/actions/workflows/verify.yml/badge.svg)](https://github.com/NachiaVivias/yawn-at-the-top/actions)

[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://NachiaVivias.github.io/yawn-at-the-top)

`src/` 及び `src-doc/` 下にあるディレクトリの中に配置されたファイルから `notebook.pdf` を生成する。

`test/` 下には、自動テストの対象となるファイルを配置する。

## フレームワーク tatyam-prime/ICPC_notebook

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

1. GitHub で新規 private repository を作る
1. yukicoder の API キーを取得し、 GitHub リポジトリの Settings -> Secrets and variables -> Actions -> New repository secret で Name=`YUKICODER_TOKEN` で登録
1.  GitHub リポジトリの Settings -> Actions -> Workflow permissions を Read and Write に設定
1. [https://competitive-verifier.github.io/competitive-verifier/installer.ja.html](https://competitive-verifier.github.io/competitive-verifier/installer.ja.html) の手順で Actions のスクリプトを作成し、 `.github/workflows/verify.yml` に保存する
1. [README.md](README.md) をいい感じに修正
1. push
1. workflow が動くことを確認


### 利用

本システムの設定は、ファイル `build/build_setting.toml` の編集によって行う。同ファイルには、設定内容の簡単な説明も書かれている。

コード自動フォーマッタの設定は、ファイル `.clang-format` の編集によって行う。

```
make build       # PDF 生成
make verify      # oj-verify
make serve       # oj-verify ページ生成
```

注意すること

* 行幅が大きくなる数式を入れると、ページ末尾にあるはずの行が PDF に出力されなくなる場合がある。
* `.clang-format` で設定した 1 行の文字数制限が PDF の横幅よりも大きいとき、変な改行が入る。
* すべてのライブラリを自動 verify する方針ではない。自動 verify がない機能を編集した後は適切に verify すること。
