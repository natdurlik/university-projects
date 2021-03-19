
#include <iostream>
using namespace std;

class A{
  public:
  virtual int oblicz(int n){
    return n*n;
  }
};

extern "C" int zmien(A & a);


int main(){
  A a, b; 
  A *pa = &a, *pb = &b; 
  cout << pa->oblicz(1) << " " << pa->oblicz(2)<< " "<< pb->oblicz(2) << endl;
  cout<<zmien(a)<<endl;
  cout << pa->oblicz(1) << " " << pa->oblicz(2)<< " "<< pb->oblicz(2) << endl;
  cout << typeid(*pa).name() << endl;
   
  return 0;
}
// Spodziewane wyjście:
// 1 4 4
// 3 6 4
