// Map! std::map vs std::unordered_map

#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>

const int kIter = 2e5;

// map vs unordered_map
template <typename T>
void InsertNumbers(long long x) {
  auto start = std::chrono::system_clock::now();
  T number_map;
  for (int i = 1; i <= kIter; ++i) number_map[i * x] = i;
  long long sum = 0;
  for (auto [k, v] : number_map) sum += (k / x) * v;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << typeid(number_map).name() << "InsertNumbers(" << x
            << "), sum: " << sum << ", took " << elapsed.count() << " sec\n";
}

// hashing pairs
struct PairIntIntHash {
  std::size_t operator()(const std::pair<int, int> &p) const {
    return std::hash<long long>()(((long long)p.first) ^
                                  (((long long)p.second) << 32));
  };
};

void InsertPairs(long long x) {
  auto start = std::chrono::system_clock::now();
  std::unordered_map<std::pair<int, int>, int, PairIntIntHash> pair_map;
  for (int i = 1; i <= kIter; ++i)
    pair_map[std::make_pair(i*x, x)] = i;
  long long sum = 0;
  for (auto [k, v] : pair_map)
    sum += (k.first / x) * v;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << typeid(pair_map).name() << "InsertNumbers(" << x
            << "), sum: " << sum << ", took " << elapsed.count() << " sec\n";
}

int main() {
  InsertNumbers<std::map<int, int>>(107897);
  InsertNumbers<std::map<int, int>>(126271);
  InsertNumbers<std::unordered_map<int, int>>(107897);
  InsertNumbers<std::unordered_map<int, int>>(126271);
  InsertPairs(126271);
  return 0;
}
