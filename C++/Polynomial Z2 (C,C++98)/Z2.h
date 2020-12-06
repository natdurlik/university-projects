//Natalia Durlik
#ifndef Z2_H
#define Z2_H
#include <iostream>
class Z2{
//private:
public:
    short int z;
//public:
    Z2();
    Z2(short int x);
    operator short int()const;
    Z2& operator+=(const Z2&Z);
    Z2& operator*=(const Z2&Z);
    Z2& operator/=(const Z2&Z);
    friend std::ostream& operator<<(std::ostream&out,const Z2&A);
    friend Z2 operator+(const Z2&A,const Z2&B);
    friend Z2 operator*(const Z2&A,const Z2&B);
    friend Z2 operator/(const Z2&A,const Z2&B);
};//end of Z2 class
#endif
