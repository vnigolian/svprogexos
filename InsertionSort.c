/* ======================================================================
 * Insertion Sort
 *
 * Version: 1.0 
 * Author: VZ Nigolian(EPFL, 2017)
 * ======================================================================
 */
#include <stdio.h>
#include <limits.h>//for INT_MAX

/* ======================================================================
 * Inserts a single number into a SORTED array
 * i.e. the array MUST be sorted for this to work
 */
void insert(int x, int n, int tab[n]);

/* ======================================================================
 * Sorts the src array and stores it in the dest array
 * This works by sequentially adding the numbers in src to dest
 * using 'insert'. By doing so, we ensure that dest is alwas sorted and
 * 'insert' can work properly.
 */
void insertionSort(int n,int src[n], int dest[n]);


/* ======================================================================
 * Copies an array's contents into another one
 * This is a helper function for the in-place 'insertionSort' function
 */
void copy(int n, int src[n], int dest[n]);

/* ======================================================================
 * Sorts the tab array in-place by first creating a new array filled with
 * INT_MAX values, then sorting tab and storing it in this new array and
 * finally copying the new array into tab.
 * The point is to hide the inner workings of the sorting procedure
 */
void insertionSortInplace(int n,int tab[n]);

/* ======================================================================
 * Prints an array
 */
void printTab(int n, int tab[n]);

int main(){
	int n=10;
	int src[] = {1,0,-3,45,-63,2,54,434,-42,10};
	printTab(n,src);
	insertionSortInplace(n,src);
	printTab(n,src);
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
	while(i<n && x>tab[i]){
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

void insertionSortInplace(int n,int tab[n]){
	int temp[n];
	for(int i=0;i<n;i++){
		temp[i]=INT_MAX;//this means that all numbers added to this
		//array will be lower than its initial contents
	}
	insertionSort(n,tab,temp);
	copy(n,temp,tab);
}

void copy(int n, int src[n], int dest[n]){
	for(int i=0;i<n;i++){
		dest[i]=src[i];
	}
}
