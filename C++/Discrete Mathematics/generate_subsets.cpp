#include <iostream>
#include <vector>
using namespace std;

const int N=7;        // generate subsets of set A[1],A[2],A[2],...,A[N]
const int K=7;
int A[N+1];

void printTab()
{
  for (int i=1;i<=K;i++)
    cout<<A[i]<<" ";
  cout<<endl;
}

void generateSubsets(void (fun)())
{
	for(int i=1;i<=K;i++) {
		A[i]=i;
	}
	int p=K;
	while(p>=1) {
		fun();
		if(A[K]==N) p--;
		else p=K;
		if(p>=1) {
			for(int i=K;i>=p;i--) {
				A[i]=A[p]+i-p+1;
			}
		}
	}
}

vector<vector<int>> generateSubsets(vector<int> A)
{
    //int N=((int)A.size())-1;
    if(N==K)
    {
        vector<int> tmp(K);
        for(int i=0;i<K;i++) tmp[i]=i+1;
        return vector<vector<int>>{tmp};
    }
    vector<vector<int>>subs;
  //  vector<int> tmp;
	for(int i=1;i<=K;i++) {
		A[i]=i;
	}
	int p=K;
	while(p>=1) {
        vector<int> tmp(A.begin()+1,A.begin()+K+1);
		subs.push_back(tmp);
		if(A[K]==N) p--;
		else p=K;
		if(p>=1) {
			for(int i=K;i>=p;i--) {
				A[i]=A[p]+i-p+1;
			}
		}
	}
	return subs;
}

int main()
{
    vector<int> A(N+1);
   vector<vector<int>> subs=generateSubsets(A);
   for(int i=0;i<subs.size();i++) {
        for(int j=0;j<subs[i].size();j++) {
            cout<<subs[i][j]<<" ";
        }
        cout<<endl;
   }
   cout<<endl;
   cout<<endl;
  // generateSubsets(printTab);

}


