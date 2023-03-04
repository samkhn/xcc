#include <iostream>

class Rectangle
{
public:
    void SetValues( int width, int height );
    int Area( ) const;
    friend Rectangle Duplicate( Rectangle &other );
private:
    int width_;
    int height_;
};

void Rectangle::SetValues( int width, int height )
{
    width_ = width;
    height_ = height;
}

int Rectangle::Area( ) const
{
    return width_ * height_;
}

// Definition of the friend function.
Rectangle Duplicate( Rectangle &other )
{
    Rectangle r;
    r.width_ = other.width_ * 2;
    r.height_ = other.height_ * 2;
    return( r );
}

int main()
{
    Rectangle a, b;
    a.SetValues( 2, 3 );
    std::cout << "A's area predup: " << a.Area() << "\n";
    std::cout << "B's area predup: " << b.Area() << "\n";
    b = Duplicate( a );
    std::cout << "A's area postdup: " << a.Area() << "\n";
    std::cout << "B's area postdup: " << b.Area() << "\n";
    return( 0 );
}
