#include <iostream>
using namespace std;

const int N=4;   // rozmiar tablicy do permutowania
int tab[N+1];	 // permutujemy tablice t[1..N] (dla wygody indeksujemy od 1)


void initTab()
{
  for (int i=1;i<=N;i++)
    tab[i]=i;
}

void printTab()
{
  for (int i=1;i<=N;i++)
    cout<<tab[i]<<" ";
  cout<<endl;
}

void swap(int i,int j)
{
   int tmp=tab[i];
   tab[i]=tab[j];
   tab[j]=tmp;
}

void reverse(int start,int stop)
{
  int i=start;
  int j=stop;
  
  while (i<j)
  {
   swap(i,j);
    ++i;--j;
  }
}

bool nextPermutation()
{
	bool rev=true;
	for(int i=2;i<=N;i++) {
		if(tab[i-1]<tab[i]) {
			rev=false;
			break;
		}
	}
	if(rev) return false;
	int k,l;
	for(int i=N;i>0;i--) {
		if(tab[i-1]<tab[i]) {
			k=i-1;
			break;
		}
	}
	for(int i=N;i>k;i--) {
		if(tab[i]>tab[k]) {
			l=i;
			break;
		}
	}
	swap(l,k);
	reverse(k+1,N);
	return true;
}

int generateAllPermutations(void (fun)())
{
	int count=1;
	fun();
	while(nextPermutation()) {
		fun();
		count++;
	}
	return count;
}


int main()
{
  initTab();
  cout<<generateAllPermutations(printTab)<<endl;
  
}
 
