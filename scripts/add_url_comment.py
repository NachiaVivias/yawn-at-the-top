#!/usr/bin/env python3

"""
vibe coding (Claude Sonnet 5.5)
以下プロンプト

以下の仕様に従って、 Python プログラムと GitHub Actions 用の `.yml` ファイルを作成してください。

## 概要

GitHub のライブラリのリポジトリについて、main ブランチの push 時に、各プログラムファイルに自動的に URL を付与する GitHub Actions を作成し、利用することを目標とします。

[AtCoder生成AI対策ルール - 20261014版](https://info.atcoder.jp/entry/llm-rules-ja)

## 仕様

### 外部仕様

main ブランチの各プログラムファイルについて、

* ファイル先頭にコメントで `BEGIN <URL>` 、
* ファイル末尾にコメントで `END <URL>`

と記されている状態が保たれるようにします。 `<URL>` は、そのファイルが閲覧できる URL です。

**ただし、** C++言語 においては特別に、コメント開始の記号をスラッシュ 3 個 `///` とします。

### 設計

Python プログラムで実装し、これが main ブランチの push 時に 1 回実行されるようにします。

Python プログラムの配置は後から自由に決められることとします。

#### Python プログラムの動作

まず、リポジトリ内（の指定範囲、特に競技に使用されうる範囲）のプログラムファイルを走査します。

次に、以下に示す手順で、各ファイルを処理します。

1. Python プログラムには、コマンドライン引数として、以下の情報が与えられます。
    * GitHub のリポジトリ名（URL 作成に必要な部分）
    * 対象のプログラムが含まれるディレクトリのパス（リポジトリのルートからの相対パス）
2. 外部仕様に示したコメントのパターンがすでに存在するかどうかを判定します。存在した場合は、削除します。検出時には、先頭・末尾に追加された空行（空白のみの行を含む）を無視します。
3. ファイルパスおよびリポジトリ名から、ファイルが公開される URL を導出し、外部仕様に従ってコメントを追記します。

#### GitHub Actions の動作

Python プログラムに、リポジトリ名の情報と、対象ディレクトリのパスを与えて実行します。実行時の作業ディレクトリはリポジトリのルートとします。

最後に、変更後のファイルを `github-actions[bot]` 名義で commit 、 push します。

### プレースホルダについて

* Python のプログラムファイルを配置する場所は、暫定的に `scripts/add_url_comment.py` としてください。
* `.yml` ファイル内について、対象ディレクトリは、暫定的に `path/to/src` としてください。

"""







"""各プログラムファイルの先頭に `BEGIN <URL>`、末尾に `END <URL>` のコメントを付与する。

使い方（リポジトリのルートで実行する）:
    python scripts/add_url_comment.py <owner/repo> <対象ディレクトリ> [--branch main]
"""

import argparse
import re
import sys
from pathlib import Path
from urllib.parse import quote

# 拡張子 -> コメント開始記号。C++ は特別にスラッシュ 3 個。
COMMENT_PREFIX = {
    # C++
    ".cpp": "///", ".cc": "///", ".cxx": "///",
    ".hpp": "///", ".hh": "///", ".h": "///",
    # // 系
    ".rs": "//", ".java": "//", ".js": "//", ".ts": "//", ".go": "//",
    ".cs": "//", ".kt": "//", ".swift": "//", ".scala": "//", ".d": "//",
    # # 系
    ".py": "#", ".rb": "#", ".sh": "#", ".jl": "#", ".nim": "#", ".pl": "#",
    # -- 系
    ".hs": "--", ".lua": "--",
}


def is_blank(line: str) -> bool:
    return line.strip() == ""


def process_text(text: str, prefix: str, url: str) -> str:
    """既存の BEGIN/END コメントを除去し、新しいものを付与したテキストを返す。"""
    bom = ""
    if text.startswith("\ufeff"):
        bom, text = "\ufeff", text[1:]
    eol = "\r\n" if "\r\n" in text else "\n"
    lines = text.splitlines()

    begin_re = re.compile(rf"^{re.escape(prefix)}\s*BEGIN\s+\S+\s*$")
    end_re = re.compile(rf"^{re.escape(prefix)}\s*END\s+\S+\s*$")

    # シェバンは先頭に残す必要があるため、その直後に BEGIN を置く
    head = []
    if prefix == "#" and lines and lines[0].startswith("#!"):
        head.append(lines.pop(0))

    # 先頭: 空行（空白のみの行を含む）を無視して BEGIN を探し、あれば空行ごと削除
    i = 0
    while i < len(lines) and is_blank(lines[i]):
        i += 1
    if i < len(lines) and begin_re.match(lines[i]):
        del lines[: i + 1]

    # 末尾: 空行を無視して END を探し、あれば後続の空行ごと削除
    j = len(lines)
    while j > 0 and is_blank(lines[j - 1]):
        j -= 1
    if j > 0 and end_re.match(lines[j - 1]):
        del lines[j - 1:]

    new_lines = head + [f"{prefix} BEGIN {url}"] + lines + [f"{prefix} END {url}"]
    return bom + eol.join(new_lines) + eol


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("repository", help="GitHub のリポジトリ名 (例: owner/repo)")
    parser.add_argument("directory", help="対象ディレクトリ（リポジトリルートからの相対パス）")
    parser.add_argument("--branch", default="main", help="URL に使うブランチ名 (既定: main)")
    args = parser.parse_args()

    root = Path.cwd()
    target = (root / args.directory).resolve()
    if not target.is_dir():
        print(f"error: directory not found: {args.directory}", file=sys.stderr)
        return 1

    changed = 0
    for path in sorted(target.rglob("*")):
        if not path.is_file():
            continue
        prefix = COMMENT_PREFIX.get(path.suffix.lower())
        if prefix is None:
            continue
        rel = path.relative_to(root.resolve())
        # 隠しディレクトリ・隠しファイルは対象外
        if any(part.startswith(".") for part in path.relative_to(target).parts):
            continue

        url = f"https://github.com/{args.repository}/blob/{args.branch}/{quote(rel.as_posix())}"
        try:
            old = path.read_bytes().decode("utf-8")
        except UnicodeDecodeError:
            print(f"skip (not utf-8): {rel}", file=sys.stderr)
            continue

        new = process_text(old, prefix, url)
        if new != old:
            path.write_bytes(new.encode("utf-8"))
            changed += 1
            print(f"updated: {rel}")

    print(f"done: {changed} file(s) updated")
    return 0


if __name__ == "__main__":
    sys.exit(main())
