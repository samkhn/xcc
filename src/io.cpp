// iostream

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

static constexpr std::string_view kFileName = "test.txt";

int32_t main() {
  int i = 10;
  double d = 15.0;
  std::string s = "data";

  std::ofstream out(kFileName.data(), std::ios::binary);
  out << i << ' ' << d << ' ' << s;
  out.close();

  std::ifstream in(kFileName.data(), std::ios::binary);
  if (!in.is_open()) {
    std::cout << "Failed to open " << kFileName << "\n";
    return -1;
  }
  int c = 0;
  int ri;
  double rd;
  std::string rs;
  while (in >> ri >> rd >> rs) {
    std::cout << "read line " << c++ << "\n";
    std::cout << "data: " << ri << rd << rs << "\n";
  }
  in.close();

  remove(kFileName.data());
  
  return 0;
}
