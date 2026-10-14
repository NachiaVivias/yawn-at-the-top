# BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/common/random.sh
while true; do
  python3 gen.py
  c="$(python3 correct.py < input.txt)"
  w="$(./a.out < input.txt)"
  if [[ "$c" = "$w" ]]; then
    echo "pass"
  else
    echo "WA"
    cat input.txt
    echo "o:"
    echo "$c"
    echo "x:"
    echo "$w"
    exit
  fi
done
# END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/common/random.sh
