#include <iostream>

class Foo {
 private:
  int member_;
 public:
  Foo( int member ) : member_ ( member ) {}
  // explicit Foo( int member ) : member_ ( member ) {}

  int GetMember() const { return member_; }
};

void DoBar( Foo foo ) {
  int i = foo.GetMember();
}

int main()
{
    // the explicit keyword above prevents compilation because 10 is not a parameter to DoBar.
    // Without explicit, the compiler will allow one conversion from int -> Foo before passing to DoBar
    //  because Foo has an int constructor.
    DoBar( 10 );
    std::cout << "DoBar( 10 ) converted to DooBar( Foo( 10 ) ) without explicit keyword\n";
}
