// Numeric
// gcd, lcm, other math functions
// iota

#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// TODO: extended Euclidean for RSA
int gcd(int a, int b) {
  if (a == 0) {
    return b;
  }
  return gcd(b % a, a);
}

// NOTE: a/g*b is preferred over a*b/g to prevent overflow
int lcm(int a, int b) {
  return a / gcd(a, b) * b;
}

template <typename Iterator>
void PrintContainerLn(std::string_view s, Iterator b, Iterator e) {
  for (std::cout << s << ": "; b != e; std::cout << *b++ << " ") {}
  std::cout << "\n";
}

int main() {
  
  int p = 2 * 4 * 5;
  int q = 2 * 4 * 6;
  assert(2 * 4 == std::gcd(p, q));
  assert(2 * 4 == gcd(p, q));

  p = 2 * 3;
  q = 2 * 5;
  assert(2 * 3 * 5 == std::lcm(p, q));
  assert(2 * 3 * 5 == lcm(p, q));

  std::vector<int> v(5, 0);
  PrintContainerLn("v (initial)", v.begin(), v.end());
  std::iota(v.begin(), v.end(), -1);
  PrintContainerLn("v (iota(-1))", v.begin(), v.end());
  return 0;
}
