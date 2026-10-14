# BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/common/build.sh
g++ a.cpp -o a -O2 -std=c++20 -fsanitize=address 2>err.txt && ./a <in.txt >out.txt 2>err.txt
# END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/src/common/build.sh
