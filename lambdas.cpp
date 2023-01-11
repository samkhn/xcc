#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

int main( )
{
    /*
      Lambda
      
      [] () mutable throw() constexpr -> int {}
      []      : capture list (required)
      ()      : parameter list
      mutable : allows lambda to modify value of variables inside impl passed into capture last that weren't passed by reference
      throw() :
      -> int  : return type
      {}      : code/instructions

      Think of lambdas like classes...
      - capture list are private data
      - when lambda is constructed, constructor copies captured variables inside
      - has an operator()(...) where args are passed in place of ...
      - has scope lifetime
      - data gets destroyed which frees members

        lambdas != std::function, lambda can be assigned to std::function objects though
        lambdas dont have a type so you have to use auto
        if capture list empty it can be assigned to a C functor
      
     */
    
    int i, j, k;

    // Capture list. List variables from the surrounding scope that will get accessed inside.
    // Can be empty: which indicates the lambda won't access anything from the enclosing scope.
    // Capture all vars inside by reference example:
    auto f1 = [&]( ){ i = 1; j = 2; k = 3; };
    f1();
    // Capture all vars inside by reference example:
    auto f2 = [=]( ){ std::cout << i << j << k << "\n"; };  // prints "123"
    f2();
    
    // Capture list mix and match possible
    // ex: [&, i, j] captures all vars by reference except for i j which are captured by value
    // not ex: [&, &i] won't work: i preceded by & when & is the default
    // ex: [=, *this]
    // not ex: [=, this] won't work: this is a pointer, when = (by value) is default
    // not ex: [i, i] won't work: i repeated.

    // Starting in C++14, you can introduce and initialize new variables in the capture clause,
    // without the need to have those variables exist in the lambda function's enclosing scope.
    auto pNums = std::make_unique<std::vector<int>>(std::vector<int>{1, 2});
    auto f3 = [ ptr = std::move(pNums) ] ()
    {
        // use ptr
    };
    f3();

    // mutable and parameter example
    int m, n = 0;
    [&m, n] (int a) mutable { m = ++n + a; }( 4 );
    // Does not compile [&m, n] (int a) { m = ++n + a; }( 4 );
    auto f4 = [ ](int m, int n) { std::cout << m << n << "\n"; };  // prints "50"
    f4(m, n);

    // exception
    std::vector<int> elements(3);
    std::vector<int> indices(3);
    indices[0] = 0;
    indices[1] = -1; // This is not a valid subscript. It will trigger an exception.
    indices[2] = 2;
    
    try
    {
        for_each(indices.begin(), indices.end(), [&](int index) {
            elements.at(index) = index;
        });
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "As expected, out of range error\n";
    }

    // Starting in C++17, lambdas can also be used to return constexpr or supply values to constexpr.
    auto add10 = [](int x) -> int
    {
        return x + 10;
    };
    constexpr int response = add10(5);
    std::cout << response << "\n";
    
    return( 0 );
}
