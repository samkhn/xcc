// CRTP (Curiously Recurring Template Pattern) aka compile time polymorphism.

#include <iostream>

template <class Derived>
struct Base {
  void name() {
    (static_cast<Derived*>(this))->impl();
  }
};

struct D1 : public Base<D1> {
  void impl() {
    std::cout << "d1 impl\n";
  }
};

struct D2 : public Base<D2> {
  void impl() {
    std::cout << "d2 impl\n";
  }
};

int main() {
  Base<D1> b1;
  b1.name();  // d1 impl
  Base<D2> b2;
  b2.name();  // d2 impl
  D1 d1;
  d1.name();  // d1 impl
  D2 d2;
  d2.name();  // d2 impl
  return 0;
}
