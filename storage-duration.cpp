// Storage duration

#include <csignal>
#include <iostream>
#include <mutex>
#include <string>

#include "inline.h"

int a( )
{
    ++counter;
    return sum( 1, 2 );
}

// static has 3 meanings depending on where it's used
// static/global var: the objects lifetime is the entire runtime of the program
// static variables are considered private to this translation unit (hence you can't declare a static variable extern)
//  (its name is not visible from outside the file in which it is declared).
static int Foo = 42;

// within local scopes, static changes a local variable from auto duration (destroy on block exit) to static.
// Variable is created at start of program and destroyed at end. Initialized once.
void IncrementAndPrint( )
{
    static int value = 1;
    ++value;
    std::cout << "Static int value is now " << value << "\n";
    // On program exit, value isn't destroyed, just inaccessible.
}

// class member var: static declares members that are not bound to class instances
// (use case is counting how many instances of that class exists).
class Dummy
{
public:
    static int n;
    Dummy() { n++; }
    ~Dummy() { n--; }
};

int Dummy::n = 0;

// const: once defined, variable cannot change (compiler can use this to make optimizations)
// Warning: this does not restrict modification via pointer or reference.
// Using a pointer or reference to modify a const variable leads to undefined behavior.
const int Bar = 420;

// Important note about const: const is not that meaningful in function decls. Examples:
void F(int);  // declares F(int)
void F(const int);  // this is a redeclaration of F(int)
void F(int) {}  // defines F(int)
// void F(const int) {};  // ERROR: redefinition of F(in)
// const type-specifiers buried within a parameter type specification are important though so use const there. Examples:
void G1(const int* x);
void G2(const int& x);
void G3(std::unique_ptr<const int> x);
void G4(int* x);
// Examples of where const isnt useful
void H1(const int x);  // becomes H1(int)
void H2(int* const x);  // becomes H2(int*)
void H3(const int* const x);  // becomes H3(const int*)

// mutable - permits modification of the class member declared mutable even if the containing object is declared const.
// use case: mutexes. M&M (mutable mutex) is a common pattern, lazy evaluation
// Used to specify that the member does not impact the externally visible state of the class.
class ThreadSafeCounter
{
    mutable std::mutex m_;
    int data_ = 0;
public:
    int get( ) const
    {
        std::lock_guard<std::mutex> lk( m_ );
        return data_;
    }

    void inc( )
    {
        std::lock_guard<std::mutex> lk( m_ );
        data_++;
    }
};

// constexpr - keyword that says that a variable or function is fit for use in a constant expression.
//   A constant expression is a location that requires compile time evaluation e.g. templates,
//   architecture specific max()/min() functions for arithmetic, array size specification.
// Evaluates the value of a function or variable at compile time
// Such variables and functions can then be used where only compile time constant expressions are allowed
// If used in object declaration, it just means const.
// If used on a function, the value returned from executing a function can be used in constexpr.
// From Google C++ style guide: Use constexpr to define true constants or to ensure constant initialization.
template <typename T, size_t N>
constexpr size_t SizeOf( T (&)[N] )
{
    return N;
}
// another demo. How to store pi?
#define ONE 1;  // this is just a bad idea
enum { TWO = 2 };  // works but isn't fully typed
// enum { pi = 3.1415f } doesn't even compile
static const float piold = 3.1415f;  // this is a file local lvalue pretending to be an rvalue. Might break depending on how statics are initialized.
constexpr float pi = 3.1415f;  // nice. Note that constexpr const just becomes constexpr

int main()
{
    // static local
    IncrementAndPrint();
    IncrementAndPrint();
    
    // static inside class
    Dummy a;
    Dummy b[5];
    Dummy *c = new Dummy;
    std::cout << "a.n = " << a.n << "\n";  // a.n = 7
    delete c;
    std::cout << "Dummy::n = " << Dummy::n << "\n";  // CDummy::n = 6

    // constexpr#1
    int x[10];
    int y[SizeOf<int>(x)];  // happens at compile time
    // without constexpr: int y[sizeof(y)/sizeof(int)]
    std::cout << "size of array y is: " << sizeof(y)/sizeof(int) << "\n";
    
    return( 0 );
}
