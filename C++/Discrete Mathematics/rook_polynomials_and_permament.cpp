#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> matrix;

vector<vector<int>> generateSubsets(vector<int> A,int K) {
    int N=((int)A.size())-1;
    if(N==K)
    {
        vector<int> tmp(K);
        for(int i=0;i<K;i++) tmp[i]=i+1;
        return vector<vector<int>>{tmp};
    }
    vector<vector<int>>subs;
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

int permament(int k,int m,int n) {// matrix m x n,  m<n, rk(matrix)
    if(k==0) return 1;
    if(n<1||m<1||k<1||k>m||k>n) {
            return 0;
    }
    int perm=0;
    vector<int> A(n+1);
    vector<int> B(m+1);
    vector<vector<int>> p=generateSubsets(A,k);
    vector<vector<int>> sub_matrix=generateSubsets(B,k);
    for(int z=0;z<sub_matrix.size();z++) {
        for(int i=0;i<p.size();i++) {
            do {
                int product=1;
                for(int j=0;j<k;j++) {
                    product*=matrix[sub_matrix[z][j]-1][p[i][j]-1];
                    if(product==0) break;
                }
                perm+=product;
            } while(next_permutation(p[i].begin(),p[i].end()));
        }
    }
    return perm;
}

//perm(A)=perm(A^T)
void transpose() {
    int m=matrix.size(),n=matrix[0].size();
    vector<vector<int>> ans(n,vector<int>(m));
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) {
            ans[j][i]=matrix[i][j];
        }
    }
    matrix=ans;
}

int main()
{
    string plik;
    cout<<"file name:"<<endl;
    cin>>plik;

    ifstream infile(plik);
    string line;
    getline(infile,line);
    istringstream iss(line);
    int m,n; //matrix size
    iss>>m;
    getline(infile,line);
    istringstream isss(line);
    isss>>n;
    matrix.resize(m,vector<int>(n));
    int i=0;
    while(getline(infile,line)) {
        for(int j=0;j<n;j++) {
            if(line[j]=='0'||line[j]=='O') matrix[i][j]=1;
            else matrix[i][j]=0;
        }
        i++;
    }
    if(m>n) transpose();


    for(int k=0;k<=min(m,n);k++)
        cout<<"x^"<<k<<"="<<permament(k,matrix.size(),matrix[0].size())<<endl;
}

