/// BEGIN https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/unit_test/directed_mst.test.cpp
// competitive-verifier: STANDALONE

#define _GLIBCXX_DEBUG

#include "src/common/template.hpp"
#include "src/graph/directed_mst.hpp"

int main() {
  V<Edge> nested_cycles = {
      {0, 1, 2}, {1, 0, 0}, {1, 2, 0},
      {2, 1, 2}, {3, 0, 2}, {3, 1, 3}};
  assert((directed_mst(4, 3, nested_cycles) == V<int>{1, 5, 2, -1}));
}
/// END https://github.com/NachiaVivias/yawn-at-the-top/blob/main/test/unit_test/directed_mst.test.cpp
