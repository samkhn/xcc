#include <functional>
#include <iostream>

struct NumHolder
{
    NumHolder( int num ) : num_( num ) {}
    
    void AddThenPrint( int i ) const
    {
        std::cout << num_ + i << "\n";
    }

    int num_;
};

void Noop() {}

void PrintNum( int i )
{
    std::cout << i << "\n";
}

int main( )
{
    // store a free function
    std::function<void(int)> fPNum = PrintNum;
    fPNum( 42 );

    // store a lambda
    std::function<void()> fPrint42 = []() { PrintNum( 42 ); };
    fPrint42( );

    // store result of std::bind
    std::function<void()> Display500 = std::bind( PrintNum, 500 );
    Display500( );

    // Can store things from inside class/struct
    // member func (without object)
    NumHolder h( 10 );
    std::function<void( const NumHolder&, int )> fAddThenPrint = &NumHolder::AddThenPrint;
    fAddThenPrint( h, 1 );
    fAddThenPrint( 10, 10 );  // this also works because constructor isn't explicit
    // member var (with object)
    std::function<void(int)> fAddThenPrint2 = std::bind( &NumHolder::AddThenPrint, h, std::placeholders::_1 );  // binds h to first arg of AddThenPrint (which replaces *this).
    fAddThenPrint2( 10 );
    
    // member var (without object)
    std::function<int( NumHolder const& )> fNum = &NumHolder::num_;
    std::cout << "NumHolder holds " << fNum( h ) << "\n";

    auto factorial = [ ] ( int n ) -> int
    {
        // store a lambda object to emulate "recursive lambda"; aware of extra overhead
        // Note: auto fac = [&](int n){...};" does not work because
        //   C++ spec forbids the referring to the auto'ed variable inside its initialization.
        std::function<int(int)> fac = [&] ( int n )
        {
            return ( n < 2 ) ? 1 : n * fac( n - 1 );
        };
        return fac( n );
    };
    for ( int i = 5; i < 8; ++i )
    {
        std::cout << i << "! = " << factorial(i) << "; ";
    }
    
    return( 0 );
}
