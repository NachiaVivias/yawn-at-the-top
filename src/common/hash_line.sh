# 標準入力から C++ ファイルを受け取り、コメント・空白・改行を削除し、md5 でハッシュする
y=""
g++ -dD -E -P -fpreprocessed - | while IFS= read x; do
y=$y$x
echo $(echo "$y" | tr -d '[:space:]' | md5sum | cut -c-2) "$x"
done
