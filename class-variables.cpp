// Class variables aka static member variables inside classes.
//
// it may be used for a variable within a class that can contain a counter with the number of objects of that class that are currently allocated

#include <iostream>

class Dummy
{
public:
    static int n;
    Dummy() { n++; }
    ~Dummy() { n--; }
};

int Dummy::n = 0;

int main()
{
    Dummy a;
    Dummy b[5];
    Dummy *c = new Dummy;
    std::cout << "a.n = " << a.n << "\n";  // a.n = 7
    delete c;
    std::cout << "Dummy::n = " << Dummy::n << "\n";  // CDummy::n = 6
    return 0;
}
