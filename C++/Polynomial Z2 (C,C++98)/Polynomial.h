//Natalia Durlik
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
//<cstring>
#define MAX(a,b) ((a<b)?b:a)
class Polynomial{
//private:
public:
    unsigned int degr;
    Z2*coeff;
//public:
    Polynomial();
    Polynomial(unsigned int d,Z2*coef);
    ~Polynomial();
    Polynomial(const Polynomial&c);
    friend Polynomial operator+(const Polynomial&a,const Polynomial&b);
    friend Polynomial operator*(const Polynomial&a,const Polynomial&b);
    friend void mod(const Polynomial&u,const Polynomial&v,Polynomial&q,Polynomial&r);
    friend Polynomial mnozenie(Polynomial&v,unsigned int n);
    friend Polynomial dzielenie(const Polynomial&u,Polynomial&v);
    friend Polynomial operator/(const Polynomial&u,const Polynomial&v);
    friend Polynomial operator%(const Polynomial&u,const Polynomial&v);
    friend std::ostream& operator<<(std::ostream&out,const Polynomial&a);
    friend std::istream& operator>>(std::istream&in,Polynomial&a);
    Polynomial& operator=(const Polynomial&a);
    Polynomial& operator+=(const Polynomial&a);
    unsigned int degree()const;
    Polynomial& operator*=(const Polynomial&a);
    const Z2& operator[](unsigned int idx) const;
    Z2& operator[](unsigned int idx);//dziala bez
    std::string toString(std::string xVar);
};//end of Polynomial class
#endif
