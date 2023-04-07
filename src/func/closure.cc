// Closures.
// A way to implement lexically scoped name bindings.
// Aka anonymous function.
// Operationally, a closure is a record storing a function and environment
//  where the environment is a mapping assoc each free variable of the func
//  w/ a value or a reference.
// Closures are to lambdas as objects are to classes.
// Classes don't exist at runtime, objects (instantiation of a class) do.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<int> v = {1, 2, 3, 4};

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  // Lambdas are expressions. So here the lambda is from [&] to };
  // The runtime object created by evaluating the expression is a closure.
  // even is a copy of the closure not the closure itself (not a closure
  // itself).
  // Each lambda expression generates a unique class to be generated during
  // compile time and an object of that class to be created at runtime.
  auto even = [&](int i) { return i % 2 == 0; };
  
  int64_t even_count = std::count_if(v.cbegin(), v.cend(), even);
  std::cout << "Contains " << even_count << " even numbers\n";
  return 0;
}
