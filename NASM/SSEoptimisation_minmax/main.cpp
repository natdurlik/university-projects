#include <cstdio>
#include <time.h>
#include <cstdlib>
using namespace std;
extern "C" int minmax(int n, int * tab, int * max, int * min);

void minmax_c(int n, int * tab, int * max, int * min) {
	for(int i=0;i<n;i++) {
		*max=*max>tab[i]?*max:tab[i];
		*min=*min<tab[i]?*min:tab[i];
	}
}



int main(){

const int rozmiar = 1000000;
   const int liczba_powtorzen = 1000; 
   int tab[rozmiar]; 
   srand(2019); 
   for(int i=0; i<rozmiar; ++i){
     tab[i] = rand() % 20192020 - 10000000;
    // tab[i]=-i;
   }
   //tab[rozmiar-1] = -20000000;
   int min, max;
   clock_t start, stop;
   start = clock();
   for(int i=0; i<liczba_powtorzen; i++){
      minmax(rozmiar, tab, &max, &min);
      //~ minmax_c(rozmiar, tab, &max, &min);
   }
   //~ printf("eax=%d\n", minmax(rozmiar, tab, &max, &min));
   printf("min = %d    max = %d\n", min, max); 
   stop = clock();
	minmax_c(rozmiar, tab, &max, &min);
	printf("C: min = %d    max = %d\n", min, max);
   printf("\n time = %f  ( %d cykli)\n", (stop - start)*1.0/CLOCKS_PER_SEC, (stop - start));
   return 0;
	
   return 0;
}