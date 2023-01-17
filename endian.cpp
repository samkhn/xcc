#include <iostream>

int main( )
{
  int A = 0x0A0B0C0D;
  std::cout << std::hex << "A = " << A << "\n";
  
  int mask = 0xFF;
  std::cout << std::hex << "a = " << (A & mask) << "\n";
  std::cout << std::hex << "a+1 = " << ((A >> 8) & mask) << "\n";
  std::cout << std::hex << "a+2 = " << ((A >> 16) & mask) << "\n";
  std::cout << std::hex << "a+3 = " << ((A >> 24) & mask) << "\n";
  return( 0 );
}
