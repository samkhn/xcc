// Random number generation

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <string>
#include <vector>

int main() {

  std::mt19937 gen32;
  std::mt19937_64 gen64;

  for (int n = 1; n != 10000; gen32(), gen64(), ++n) {}

  assert(gen32() == 4123659995);
  assert(gen64() == 9981545732273789042);

  std::random_device rd{};
  std::mt19937 gen{rd()};

  // std::shuffle numbers with random generator
  std::vector<int> l(10);
  std::iota(l.begin(), l.end(), -5);

  std::cout << "Pre shuffle: ";
  for(auto i : l) std::cout << i << " ";
  std::cout << "\n";

  std::shuffle(l.begin(), l.end(), gen);

  std::cout << "Post shuffle: ";
  for(auto i : l) std::cout << i << " ";
  std::cout << "\n";

  // Simulate a 6 sided die with uniform distribution
  std::uniform_int_distribution<> die(1, 6);
  std::cout << "10 die rolls: ";
  for (int n = 0; n != 10; ++n) std::cout << die(gen) << " ";
  std::cout << "\n";

  // Normal distribution
  std::normal_distribution<> d{5, 2};

  std::map<int, int> hist;
  for (int n = 0; n != 10000; ++n) {
    ++hist[std::round(d(gen))];
  }

  for (auto [x, y] : hist) {
    std::cout << std::setw(2) << x << ' ' << std::string(y/200, '*') << "\n";
  }

  return 0;

}
