// Defer

#include <iostream>

template <typename F> struct Deferred {
  F f_;
  Deferred(F f) : f_(f) {}
  ~Deferred() { f_(); }
};

template <typename F> Deferred<F> defer_func(F f) { return Deferred<F>(f); }

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x) DEFER_2(x, __COUNTER__)
#define defer(code) auto DEFER_3(_defer_) = defer_func([&]() { code; })

int some_func() {
  char *buffer = (char *)malloc(10);
  if (!buffer) {
    std::cout << "Failed to alloc\n";
    return -1;
  }
  defer(free(buffer));
  buffer[0] = 'h';
  buffer[1] = 'e';
  buffer[2] = 'l';
  buffer[3] = 'l';
  buffer[4] = 'o';
  buffer[5] = '\0';
  std::cout << buffer << "\n";
  return 0;
}

int main() { return some_func(); }
