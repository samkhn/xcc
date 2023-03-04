#include <iostream>

// Variables store values for later calling
// Here we are storing the int type under the value name
struct Variable { typedef int value; };
struct AnotherVariable { enum { value = 2 }; };

// Functions map 1+ input(s) to output
// TMP analog to this is a template class
template <int X, int Y>
struct Adder { enum { result = X + Y }; };
// You can call this at compile time with Adder<1, 2>::result. Compiler will expand this to 3.

// Branching
// Ex: this tells us that SameType<X, Y>::result == 0 and that SameType<X, X>::result == 1 where X and Y are types
template <typename X, typename Y>
struct SameType { enum { result = 0 }; };

template <typename X>
struct SameType<X, X> { enum { result = 1 }; };

// Recursion. Oh f---
template <unsigned n>
struct Factorial { enum { result = n * Factorial<n-1>::result }; };

template<>
struct Factorial<0> { enum { result = 1 }; };

// choose between two types based on a compile-time constant
template <bool Condition, typename TrueType, typename FalseType>
class If_;

template <typename TrueType, typename FalseType>
class If_<true, TrueType, FalseType> { public: typedef TrueType result; };

template <typename TrueType, typename FalseType>
class If_<false, TrueType, FalseType> { public: typedef FalseType result; };

int main( )
{
    std::cout << Factorial<5>::result << "\n";

    typename If_<true, int, void*>::result number( 3 );
    typename If_<false, int, void*>::result pointer( &number );

    typedef typename If_<(sizeof(void*)>sizeof(uint32_t)), uint64_t, uint32_t>::result integral_ptr_t;

    integral_ptr_t ConvertedPointer = reinterpret_cast<integral_ptr_t>(pointer);
    std::cout << "sizeof(integral_ptr_t) = " << sizeof(integral_ptr_t) << "\n";
    
    return( 0 );
}
