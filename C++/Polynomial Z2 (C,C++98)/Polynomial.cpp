//Natalia Durlik
#include "Z2.h"
#include "Polynomial.h"

//konstruktory
Polynomial::Polynomial():degr(0){
        coeff=new Z2[1];
        *(coeff)=Z2(0);
}
Polynomial::Polynomial(unsigned int d,Z2*coef){
    coeff=new Z2[d+1];
    degr=d;
    for(unsigned int i=0;i<d+1;i++)
    {
        *(coeff+i)=*(coef+i);
        if(*(coeff+i)==1) degr=i;
    }
}
Polynomial::~Polynomial(){//dekonstruktor
    delete[]coeff;
}
Polynomial::Polynomial(const Polynomial&c):degr(c.degr){
    coeff=new Z2[degr+1];
    for(unsigned int i=0;i<degr+1;i++)
    {
        *(coeff+i)=*(c.coeff+i);
    }
}

//metody
Polynomial& Polynomial::operator=(const Polynomial&a){
    if(this!=&a)//referencja bo nam chodzi o adresy
    {
        delete[] coeff;
        this->degr=a.degr;
        this->coeff=new Z2[this->degr+1];
        for(unsigned int i=0;i<degr+1;i++)
        {
            *(this->coeff+i)=*(a.coeff+i);
        }
    }
    return *this;
}
Polynomial& Polynomial::operator+=(const Polynomial&a){
    return *this=*this+a;
}
unsigned int Polynomial::degree()const{
    return degr;
}
Polynomial& Polynomial::operator*=(const Polynomial&a){
    return *this=*this*a;
}
const Z2& Polynomial::operator[](unsigned int idx) const{
    if(idx<=degr&&idx>=0) return coeff[idx];
    else
    {
        std::cout<<"Niepoprawny indeks wielomianu\n";
        return coeff[0];
    }
}
Z2& Polynomial::operator[](unsigned int idx){
    if(idx<=degr&&idx>=0) return coeff[idx];
    else
    {
        std::cout<<"Niepoprawny indeks wielomianu\n";
        return coeff[0];
    }
}
std::string Polynomial::toString(std::string xVar){
    std::string polyn;
    if(coeff[0]!=0||(coeff[0]==0&&degr==0))
    {
        std::ostringstream s;
        s<<coeff[0];
        polyn+=s.str();
    }
    if(coeff[0]!=0&&0!=degr)
    {
        polyn+="+";
    }
    for(unsigned int i=1;i<degr+1;i++)
    {
        if(coeff[i]!=0)
        {
            std::ostringstream ss;
            ss<<i;
            polyn+=xVar+"^"+ss.str();
            if(i!=degr)
            {
                polyn+="+";
            }
        }
    }
    return polyn;
}

//globalne
Polynomial operator+(const Polynomial&a,const Polynomial&b){
    unsigned int deg=MAX(a.degr,b.degr);
    Z2*coef=new Z2[deg+1];
    unsigned int c=0;
    for(unsigned int i=0;i<deg+1;i++)
    {
        *(coef+i)=Z2(0);
        if(i<a.degr+1)
        {
            *(coef+i)+=*(a.coeff+i);
        }
        if(i<b.degr+1)
        {

            *(coef+i)+=*(b.coeff+i);
        }
        if(*(coef+i)==1) c=i;
    }

    Polynomial C(c,coef);
    delete[] coef;
    return C;
}
std::ostream& operator<<(std::ostream&out,const Polynomial&a){
    out<<"{"<<a.coeff[0];
    for(unsigned int i=1;i<a.degr+1;i++)
    {
        out<<","<<a.coeff[i];
    }
    out<<"}";
    return out;
}
std::istream& operator>>(std::istream&in,Polynomial&a){
    std::string buff;
    getline(in,buff,'}');
    int c=0;
    while(buff[c]!='{')
    {
        c++;
    }
    int n=0;
    c++;//wskazuje teraz na 1 liczbe
    while(c<buff.length())
    {
        if(buff[c]==',')
        {
            c++;
            continue;
        }
        n++;
        a.coeff=(Z2*)realloc(a.coeff,n*sizeof(Z2));
       /* if(a.coeff==NULL)
        {
            std::cout<<"error";
            break;
        }*/
        if(buff[c]=='1')
        {
            a.degr=n-1;
            a.coeff[n-1]=1;
        }
        else
        {
           a.coeff[n-1]=0;

        }
        c++;
    }
    return in;
}
Polynomial operator*(const Polynomial&a,const Polynomial&b){
        unsigned int c=0;
        unsigned int deg=a.degr+b.degr;
        Z2*coef=new Z2[deg+1];

        for(unsigned int i=0;i<a.degr+1;i++)
        {
            for(unsigned int j=0;j<b.degr+1;j++)
            {
                coef[i+j]=coef[i+j]+(a.coeff[i]*b.coeff[j]);
                if(coef[i+j]==1&&(i+j)>c)
                {
                    c=i+j;
                }
            }
        }
        Polynomial C(c,coef);
        delete[] coef;
        return C;
}
Polynomial dzielenie(const Polynomial&u,const Polynomial&v){
    unsigned int deg=u.degr-v.degr;
    Z2*coeff=new Z2[deg+1];
    coeff[deg]=1;
    Polynomial q(deg,coeff);
    delete[] coeff;
    return q;
}
Polynomial mnozenie(const Polynomial&v,unsigned int n)//przesuniecie v do ^n
{//da sie tu dac stare r.degr zamiast n
    unsigned int deg=v.degr+n;
    Z2*coeff=new Z2[deg+1];
    for(int i=deg;i>=0;i--)
    {
        if(i>=n)
        {
            coeff[i]=v.coeff[i-n];
        }
        else//jest juz wyzerowana?
        {
            coeff[i]=0;
        }
    }
    Polynomial r(deg,coeff);
    delete[] coeff;
    return r;
}
void mod(const Polynomial&u,const Polynomial&v,Polynomial&q,Polynomial&r){
    if(v.degr!=0)
    {
        r=u;
        q=Polynomial();
        int k=0;
        while(r.degr>=v.degr)
        {
            Polynomial pom=dzielenie(r,v);
            q+=pom;
            r+=mnozenie(v,pom.degr);
            k++;
        }
    }
    else//v.degr=0
    {
        if(v.coeff[0]==1)
        {
            q=u;
            r=Polynomial();
        }
        else//v.coeff[0]==0
        {
            std::cout<<"Dzielenie przez zero\n";
        }
    }
}
Polynomial operator/(const Polynomial&u,const Polynomial&v){
    Polynomial q;
    Polynomial r;
    if(v.degr==0&&v.coeff[0]==0)
    {
        std::cout<<"Dzielenie przez zero\n";
        return u;
    }
    else
    {
        mod(u,v,q,r);
        return q;
    }
}
Polynomial operator%(const Polynomial&u,const Polynomial&v){
    Polynomial q;
    Polynomial r;
    if(v.degr==0&&v.coeff[0]==0)//kolejnosc
    {
        std::cout<<"Dzielenie przez zero\n";
        return Polynomial();
    }
    else
    {
        mod(u,v,q,r);
        return r;
    };
}

