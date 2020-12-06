#include <iostream>
using namespace std;
const int N=8;
const int A[N][N]={
    {0, 0, 0, 1, 1, 0, 1, 1},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 1, 0, 1},
    {0, 1, 0, 0, 1, 0, 0, 0},
    {1, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0}};
bool DOP[N];
int X[N];
bool one=false;
void hamilton_aux(int k) {
    for(int u=0;u<N;u++) {
        if(A[u][X[k-1]]==1) {
            if(k==N&&u==X[0]) {
                for(int i=0;i<N;i++)
                    cout<<X[i]+1<<" ";
                cout<<X[0]+1<<endl;
                //one=true;
                //return;
            }
            else {
                if(DOP[u]) {
                    X[k]=u;
                    DOP[u]=false;
                    hamilton_aux(k+1);
                    if(one) return;
                    DOP[u]=true;
                }
            }
        }
    }
}
void hamilton(int wp=0) {
    X[0]=wp;
    for(int i=0;i<N;i++) DOP[i]=true;
    DOP[wp]=false;
    hamilton_aux(1);
}


int main() {
    hamilton();
}
