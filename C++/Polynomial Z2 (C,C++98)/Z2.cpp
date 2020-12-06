//Natalia Durlik
#include "Z2.h"
#include <iostream>
//konstruktory
Z2::Z2():z(0){}
Z2::Z2(short int x){
    if(x<0) x=-x;
    z=x%2;
}
//metody
Z2::operator short()const{
    return z;
}
Z2& Z2::operator+=(const Z2&Z){
    if((Z.z==1)^(z==1)) return *this=this->z=1;
    else return *this=this->z=0;
}
Z2& Z2::operator*=(const Z2&Z){
    if(Z.z==0||z==0) return *this=this->z=0;
    else return *this=this->z=1;
}
Z2& Z2::operator/=(const Z2&Z){
    if(Z.z==0) std::cout<<"Dzielenie przez zero\n";
    return *this;
}
//globalne
Z2 operator+(const Z2&A,const Z2&B){
    Z2 C(A.z+B.z);
    return C;
}
Z2 operator*(const Z2&A,const Z2&B){
    Z2 C(A.z*B.z);
    return C;
}
Z2 operator/(const Z2&A,const Z2&B){
    if(B.z==0) std::cout<<"Dzielenie przez zero\n";
    return A;
}
std::ostream& operator<<(std::ostream&out,const Z2&A){
    return out<<A.z;
}
