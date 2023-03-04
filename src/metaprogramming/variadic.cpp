// Variadic Templates

#include <iostream>
#include <string>

// Variadic templates are written just the way you'd write recursive code (base and general (recurse) case).
// In variadic templates, you'll often use:
// - typename... Args is a template parameter pack
// - Args... args is a function parameter pack
// https://en.cppreference.com/w/cpp/language/parameter_pack
// Expansion can generate a list of ,-separated patterns where , is a list delimiter.
// The base case will be small and fixed number of params
// but the general case will make use of parameter packs and usually will peel off parameters.

// Advantage?
// Better than C variadics because C variadics are resolved at runtime, C++ template variadics are resolved at compile time.

// DEBUGGING:
// To get a better feel for the process, one can use the __PRETTY_FUNCTION__ macro (gcc/clang) or __FUNCSIG__ (MSVC)
// If we insert the following as the first line in both versions of Adder
//  std::cout << __FUNCSIG__  << std::endl;
// we'll see the template expansion
// You can try to insert WHATIS<T>() after forward declaring: template<typename... Args> void WHATIS();
// Upon an error, the compiler will spit out what T is.

// EXAMPLES:
// Adder works on any type that implements the + operator
template <typename T>
T Adder( T value )
{
    // std::cout << __FUNCSIG__  << std::endl;
    return value;
}

template <typename T, typename... Args>
T Adder( T first, Args... args )
{
    // std::cout << __FUNCSIG__  << std::endl;
    // We "peel off" the first and add to it.
    return first + Adder( args... );
}

// PairCmp assumes each pair is comparable (not necessarily that they are the same type)
template <typename T>
bool PairCmp( T value )
{
    return false;
}

template <typename L, typename R>
bool PairCmp( L a, R b )
{
    return a == b;
}

template <typename L, typename R, typename... Args>
bool PairCmp( L a, R b, Args... args)
{
    return ( a == b ) && PairCmp( args... );
}

// Tuple, example of a variadic data structure
template <typename... Ts> struct Tuple {};

template <typename T, typename... Ts>
struct Tuple<T, Ts...> : public Tuple<Ts...>
{
    Tuple(T t, Ts... ts) : Tuple<Ts...>(ts...), tail( t ) {};
    T tail;
};

// We use Get to access members of Tuple for reading/writing.

// ElemTypeHolder is yet another variadic class template.
// It takes a number k and the tuple type we're interested in as template parameters.
// e.g. ElemTypeHolder<2, SomeTupleType> peels off 2 types and sets Type to the 3rd.
template <std::size_t, typename> struct ElemTypeHolder;

template <typename T, typename... Ts>
struct ElemTypeHolder<0, Tuple<T, Ts...>>
{
    // TODO(samiurkh1n): if we replace type with Type throughout, templated function lookup for Get() fails. Why?
    using type = T;
};
template <std::size_t K, typename T, typename... Ts>
struct ElemTypeHolder<K, Tuple<T, Ts...>>
{
    using type = typename ElemTypeHolder<K-1, Tuple<Ts...>>::type;
};

// With ElemTypeHolder, we can implement Get
template <std::size_t K, typename... Ts>
typename std::enable_if<K == 0, typename ElemTypeHolder<0, Tuple<Ts...>>::type&>::type Get( Tuple<Ts...>& t )
{
    return t.tail;
}

template <std::size_t K, typename T, typename... Ts>
typename std::enable_if<K != 0, typename ElemTypeHolder<K, Tuple<T, Ts...>>::type&>::type Get( Tuple<T, Ts...>& t )
{
    Tuple<Ts...>& base = t;
    return Get<K-1>( base );
}

int main( )
{
    int sum = Adder( 1, 2, 3 );
    std::cout << sum << "\n";  // prints 1+2+3=6
    std::string s1 = "he", s2 = "ll", s3 = "o";
    std::cout << Adder( s1, s2, s3 ) << "\n";

    std::cout << PairCmp(1.5, 1.5, 2, 2, 6, 6) << "\n";
    std::cout << PairCmp(1.5, 1.5, 2, 2, 6, 7) << "\n";
    // next line won't compile unless we have a default false base case for single elements
    std::cout << PairCmp(1.5, 1.5, 2, 2, 6, 6, 7) << "\n";

    Tuple<double, uint64_t, const char*> t1(12.2, 42, "big");
    std::cout << "0th elem is " << Get<0>(t1) << "\n";
    std::cout << "1th elem is " << Get<1>(t1) << "\n";
    std::cout << "2th elem is " << Get<2>(t1) << "\n";
    Get<1>(t1) = 103;
    std::cout << "1th elem is " << Get<1>(t1) << "\n";
    return( 0 );
}
