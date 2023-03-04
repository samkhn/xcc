// Polymorphism
//
// Add /d1reportSingleClassLayout{Class name} to MSVC to print out class memory layout during compile time.

#include <iostream>

class Base
{
public:
    int A;
    float B;

    virtual void Foo()
    {
        std::cout << "Base!\n";
    }
};

class Derived : public Base
{
public:
    int C;
    double D;
    
    virtual void Foo()
    {
        std::cout << "Child!\n";
    }
};

int main()
{
    Base first;
    Derived second;

    first.Foo();
    second.Foo();

    std::cout << "Base.A offset: " << (size_t)&first.A - (size_t)&first << "\n";
    std::cout << "Base.B offset: " << (size_t)&first.B - (size_t)&first << "\n";

    std::cout << "Derived.A offset: " << (size_t)&second.A - (size_t)&second << "\n";
    std::cout << "Derived.B offset: " << (size_t)&second.B - (size_t)&second << "\n";
    std::cout << "Derived.C offset: " << (size_t)&second.C - (size_t)&second << "\n";
    std::cout << "Derived.C offset: " << (size_t)&second.C - (size_t)&second << "\n";
    
    return( 0 );
}
