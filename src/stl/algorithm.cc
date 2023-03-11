// Interesting parts of C++17 algorithm library.
// Keywords explored:
//  unique, binary_search, fill, rotate, merge, and partition[_point].

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Alternative implementation
// std::cout << s << ": ";
// std::copy(b, e, std::ostream_iterator<int>(std::cout, " "));
// std::cout << "\n";
template <typename Iterator>
void PrintContainerLn(std::string_view s, Iterator b, Iterator e) {
  for (std::cout << s; b != e; std::cout << *b++ << ' ') {}
  std::cout << '\n';
}

int main() {
  
  std::vector<int> v = {1, 1, 2, 2, 3, 2, 1};
  PrintContainerLn("v: ", v.begin(), v.end());

  // print with offset by adding int to start iterator
  int offset = 2;
  PrintContainerLn("v w/ offset 2: ", 2+v.begin(), v.end());

  // std::unique removes consecutive adjacent duplicates.
  // returns iterator to last valid element
  // If you are trying to dedup all of the vector, std::sort first
  std::sort(v.begin(), v.end());
  auto l = std::unique(v.begin(), v.end());
  v.erase(l, v.end());
  PrintContainerLn("dedup(v): ", v.begin(), v.end());

  // Search sorted container with std::binary_search
  if (std::binary_search(v.begin(), v.end(), 2)) {
    std::cout << "\tbinary_search(dedup(v), 2) contains 2\n";
  }

  // std::fill instead of memset
  std::vector<int> u; u.resize(5);
  std::fill(u.begin(), u.end(), 2);
  PrintContainerLn("u: ", u.begin(), u.end());

  // Cyclic shift of a vector by k with std::rotate (instead of looping and
  // swapping i with i+1). std::rotate(b, m, e). m becomes first from b to e
  std::vector<int> w({1, 2, 3, 4, 5});
  PrintContainerLn("w: ", w.begin(), w.end());
  std::rotate(w.begin(), w.begin() + 2, w.end());
  PrintContainerLn("w, rotated: ", w.begin(), w.end());

  // If there is a predicate p(x) where the first set of elements returns true
  // and the other elements returns false, you can use partition_point to find
  // it. Following example partitions at first even number.
  std::vector<int> il({1, 2, 3, 4, 5, 6, 7, 8, 9});
  PrintContainerLn("il: ", il.begin(), il.end());
  auto is_even = [](int i) { return i % 2 == 0; };
  std::partition(il.begin(), il.end(), is_even);
  PrintContainerLn("il, partitioned into even/odd: ", il.begin(), il.end());
  auto i = std::partition_point(il.begin(), il.end(), is_even);
  PrintContainerLn("il even elements: ", il.begin(), i);
  PrintContainerLn("il  odd elements: ", i, il.end());

  // You can merge multiple lists. Merges the lists in sorted manner.
  // Make sure to allocate enough memory to hold the merged lists.
  PrintContainerLn("u: ", u.begin(), u.end());
  PrintContainerLn("v: ", v.begin(), v.end());
  std::vector<int> m;
  m.resize(u.size() + v.size());
  std::merge(u.begin(), u.end(), v.begin(), v.end(), m.begin());
  PrintContainerLn("merge(u, v): ", m.begin(), m.end());
  
  return 0;
}
