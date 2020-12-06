#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;


//N>2
const int N=10; //vertexes: V={1,2,...,N};
vector<vector<int>> adj_list(N);
//int T[N][N]={};




int min_el(vector<int> &L1,vector<int> &L2,int j) {
    int min_idx=-1;
    int i=0;
    while(min_idx==-1) {
        if(find(L1.begin()+j,L1.end(),L2[i])==L1.end()) {
            min_idx=i;
            break;
        }
        i++;
    }
    return min_idx;
}

void random_tree_generating() {//N>2
    vector<int> L1(N-2);
    vector<int> L2(N);
    for(int i=0;i<N;i++) L2[i]=i+1;
    generate(L1.begin(),L1.end(),[](){return rand()%N+1;});
    int i,j;
    //for(int i=0;i<L1.size();i++) cout<<L1[i]<<" ";
    //cout<<endl;
    for(int j=0;j<L1.size();j++) {
        i=min_el(L1,L2,j);
        adj_list[L2[i]-1].push_back(L1[j]);
        adj_list[L1[j]-1].push_back(L2[i]);
        L2.erase(L2.begin()+i);
    }
    adj_list[L2[0]-1].push_back(L2[1]);
    adj_list[L2[1]-1].push_back(L2[0]);
}

void show_tree() {
    for(int i=0;i<N;i++) {
        cout<<"neigh: "<<i+1<<":  ";
        for(int j=0;j<adj_list[i].size();j++) {
            cout<<adj_list[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main() {
    srand(unsigned(time(0)));
    random_tree_generating();
    show_tree();
    return 0;
}
