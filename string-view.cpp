#include <iostream>
#include <string>

// C convention
void TakesCharStar( const char* s ) {}

// Old
void TakesString( const std::string& s ) {}

// C++17
// DO: always pass string_view by value
void TakesStringView( std::string_view s ) {}

int main( )
{
    std::string messageCpp = "HelloCpp";
    const char *messageC = "HelloC";
    
    // Old+C way tends to not work well if you don't know types in advance
    // e.g. what happens if you need to convert c str <-> std::string?
    // Unnecessary copies happen
    TakesCharStar( messageCpp.c_str( ) );
    TakesString( std::string(messageC) );  // compiler makes a copy

    // String view is better
    //  can be thought of as a “view” into an existing character buffer
    //  contains only a pointer and a length
    //  cannot be used to modify what it is looking at
    //  copying a string_view is a shallow copy
    //  (again we see here, object that manages != object that owns resource/memory
    TakesStringView( messageCpp );
    TakesStringView( messageC );
    
    // WARNING: string_view is not necessarily NUL-terminated
    std::string_view nice = "Nice"; 
    std::cout << nice << "\n";
    
    return( 0 );
}
