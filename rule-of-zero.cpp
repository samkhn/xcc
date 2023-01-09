// Demo of rule of zero, three, five with a preference for zero.
// Rule of 3/5/0
//
// Rule of three and five state are based on the idea that an object that cleans up a resource in its desctructor owns that resource.
//
// When you implement any class/type, you have to handle what happens if you move or copy the resource.
// C++ allows you to define a copy constructor, copy assignment operator, etc.
//
// Rule of 3: if you define any of the 3 you should define the others: destructor, copy constructor, copy assignment operator
// Rule of 5: in addition to rule of 3, given move semantics you also should define a move operator and a move assignment operator.
// (for rule of 5 you might need to use std::move (equivalent to a static_cast to an rvalue reference type).
//
// As suggested by this article: http://flamingdangerzone.com/cxx11/2012/08/15/rule-of-zero.html
// it might just be better to use rule of zero, where you break from the convention of object that destroys a resource owns it
// and instead have the object and resource be seperate entities. You can do this by having the resource accessible via
// std::unique_ptr or std::shared_ptr. Rule of zero has two benefits: exception safety and cleaner code.
//
// Examples below.

#include <memory>
#include <stdlib.h>
#include <string.h>
#include <string>

static char LIBRARY[100];

void* LoadLibrary( const char *name )
{
    strcpy_s( LIBRARY, _countof( LIBRARY ), name );
    return &LIBRARY;
}

void FreeLibrary( )
{
    strcpy_s( LIBRARY, _countof( LIBRARY ), "0" );
}

class ModuleOld
{
public:
    explicit ModuleOld( std::string const &name ) : handle_ { LoadLibrary( name.c_str() ) } {}

    // Move constructor
    ModuleOld( ModuleOld &&that ) : handle_ { that.handle_ } { that.handle_ = nullptr; }
    // Copy constructor is implicitly forbidden

    ModuleOld& operator=( ModuleOld &&that )
    {
        ModuleOld copy { std::move( that ) };
        std::swap( handle_, copy.handle_ );
        return *this;
    }
    // Copy assignment operator is implicitly forbidden

    ~ModuleOld( )
    {
        FreeLibrary( );
    }

    // Other module related functions
    
private:
    void* handle_;
};

// Or you can implement this with rule of zero.
// Here lifetime of the resource is implicitly managed by the compiler.
// No duplication of ownership logic
// Less code, less surface for bugs
// No mixing of ownership with other issues
// Exception safety (say in case memory runs out, things will clean up since std::unique_ptr can destruct).
class Module
{
public:
    explicit Module( std::string const &name )
        : handle_ { std::make_unique<void *>( LoadLibrary( name.c_str() ) ) } {}

    // Other module related functions
private:
    std::unique_ptr<void*> handle_;
};

// Example of exception safety
// What if allocating two throws? We would need to clean up resource one.
struct Something
{
    Something()
        : one { new Module( "a" ) },
          two { new Module( "b" ) } {}

    // Other
    Module *one;
    Module *two;
};
// Rule of zero:
// Classes that have custom destructors, copy/move constructors or copy/move assignment operators should deal exclusively with ownership.
// Other classes should not have custom destructors, copy/move constructors or copy/move assignment operators.

int main()
{
    Something s;
    return 0;
}
