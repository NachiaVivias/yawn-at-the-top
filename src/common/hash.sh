# BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/common/hash.sh
# 標準入力から C++ ファイルを受け取り、コメント・空白・改行を削除し、md5 でハッシュする
g++ -dD -E -P -fpreprocessed - | tr -d '[:space:]' | md5sum | cut -c-6
# END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/common/hash.sh
