// Variant. The C++ take on unions.

#include <iostream>
#include <string>
#include <variant>

struct ExampleVisitor {
  void operator()(int i) const {
    std::cout << "int: " << i << "\n";
  }
  void operator()(float f) const {
    std::cout << "float: " << f << "\n";
  }
  void operator()(const std::string &s) const {
    std::cout << "str: " << s << "\n";
  }
};

int main() {
  std::variant<int, float, std::string> v;
  std::cout << "variant<int, float, string> v holds "
            << std::variant_size_v<decltype(v)> << " types\n";

  // we visit first alternative
  std::visit(ExampleVisitor{}, v);

  std::cout << "v.index() = " << v.index() << "\n";
  v = 1.0f;
  std::cout << "v.index() = " << v.index() << "\n";
  v = "yes";
  std::cout << "v.index() = " << v.index() << "\n";

  // get_if
  const auto has_int = std::get_if<int>(&v);
  if (has_int) {
    std::cout << "int!\n";
  } else {
    std::cout << "no int!\n";
  }
  
  // NOTE: std::get_if<bool>(&v) doesn't compile
  // assertion that bool exists in set of types fails

  if (std::holds_alternative<int>(v)) {
    std::cout << "the variant holds an int!\n";
  } else if (std::holds_alternative<float>(v)) {
    std::cout << "the variant holds a float\n";
  } else if (std::holds_alternative<std::string>(v)) {
    std::cout << "the variant holds a string\n";
  }

  // try/catch and bad_variant_access
  try {
    auto f = std::get<float>(v); 
    std::cout << "float! " << f << "\n";
  } catch (std::bad_variant_access&) {
    std::cout << "our variant doesn't hold float at this moment...\n";
  }
}
