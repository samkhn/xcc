// Type casting demo
//
// Examples of how type casting works

#include <iostream>

using namespace std;

class Base {};
class Derived : public Base {};
class Unrelated {};

void constCastPrintDemo( char *message )
{
    cout << message << "\n";
}

int main()
{
    // Implicit conversion
    {
        short a = 1000;
        int b;
        b = a;
        cout << "Short with value: " << a << " is size " << sizeof(a)
             << ", int has same value " << b << " and is size "<< sizeof(b) << "\n";
    }

    // C-style explicit conversion
    // When you use this, the C++ compiler will try to interpret it in the following order:
    // const_cast -> static_cast -> static_cast followed by const_cast -> reinterpret_cast -> reinterpret_cast followed by const_cast
    {
        short c = 1000;
        int d;
        d = (int) c;
        cout << "Short with value: " << c << " is size " << sizeof(c)
             << ", int has same value " << d << " and is size "<< sizeof(d) << "\n";
    }

    // There are four types of casting that comes with C++:
    // static_cast, const_cast, reinterpret_cast, dynamic_cast

    // static_cast converts pointers between related classes and implicit conversions
    {
        double pi = 3.14159265;
        int i = static_cast<int>(pi);  // becomes 3
        cout << "Converted pi {" << pi << "} into integer: {" << i << "}\n";
    }
    // Allows conversion of derived-to-base AND base-to-derive (the latter doesn't make sense physically but allows it)
    {
        Base *b = new Base;
        Derived *d = static_cast<Derived *>(b);
        // Following line does not compile: static_cast does not allow for conversions between unrelated types
        // Unrelated *r = static_cast<Unrelated *>(d);
        delete b;
    }

    // reinterpret_cast allows conversion between pointers of unrelated types
    // Please only use this when necessary or if you know what you are doing (you probably don't)
    {
        Base *b = new Base;
        Unrelated *r = reinterpret_cast<Unrelated *>(b);
        delete b;
    }
    
    // const_cast adds/remove const-ness
    {
        const char *m = "This was a const char * passed to a char *\n";
        // constCastPrintDemo( m ); does not compile. Cannot convert arg1 from const char* to char*
        constCastPrintDemo( const_cast<char *>( m ) );
    }

    // dynamic_cast can only be used for pointers or references to object.
    // It does work to ensure that the result of the type conversion is a valid complete object of the requested class
    // e.g. cannot do base->derived class conversion (which static_cast allows)
    {
        Base b;
        Derived d;
        Base *pb = dynamic_cast<Base *>(&d);  // Okay
        // Derived *pd = dynamic_cast<Derived *>(&b);  // Does not compile. 'Base' is not a polymorphic type.
    }

    return( 0 );
}
