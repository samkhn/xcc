// Interrogating the C++ language abstract machine's object model

#include <iostream>
using namespace std;

struct S
{
    short y;
    char z;
};

int main()
{
    S Arr[3], x;
    S *pBegin = &Arr[0];
    S *pEnd = &Arr[2];
    S *pX = &x;

    cout << "pBegin == pEnd? " << (pBegin == pEnd ? "Yes" : "No") << "\n";
    cout << "pBegin == pX? " << (pBegin == pX ? "Yes" : "No") << "\n";
    cout << "pBegin != pX? " << (pBegin != pX ? "Yes" : "No") << "\n";
    cout << "pBegin < pEnd? " << (pBegin < pEnd ? "Yes" : "No") << "\n";
    
    // This last one is undefined behavior according to the C++ spec.
    // Regardless, the microsoft compiler handles it.
    cout << "pBegin < pX? " << (pBegin < pX ? "Yes" : "No") << "\n";
    return( 0 );
}
