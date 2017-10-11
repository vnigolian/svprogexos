#include <stdio.h>


void insert(int x, int n, int tab[n]);
void insertionSort(int n,int src[n], int dest[n]);
void printTab(int n, int tab[n]);

int main(){
	int n=10;
	int src[] = {1,4,3,45,63,2,54,434,42,10};	
	int dest[n];
	for(int i=0;i<n;i++){
		dest[i]=0;
	}
	
	printTab(n,src);
	insertionSort(n,src,dest);
	printTab(n,dest);
	
	return 0;
}


void printTab(int n, int tab[n]){
	printf("{");
	for(int i=0;i<n-1;i++){
		printf("%i,",tab[i]);
	}
	printf("%i}\n",tab[n-1]);
}

void insert(int x, int n, int tab[n]){
	int i=0;
	while(i<n && tab[i] !=0 &&x>tab[i]){
		i++;
	}
	if(i<n){
		for(int j=n-1;j>i;j--){
			tab[j] = tab[j-1];
		}
		tab[i]=x;
	}
}

void insertionSort(int n, int src[n],int dest[n]){
	for(int i=0;i<n;i++){
		insert(src[i],n,dest);
	}
}

