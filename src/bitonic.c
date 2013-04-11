/* Code largely based off the sample implementation
 * provided by fh-flensburg.de:
 * http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/bitonic/bitonicen.htm
 */
#include <stdio.h>
#include <stdlib.h>

void sort(int* arr, int len);
void bitonicSort(int lo, int n, int dir);
void bitonicMerge(int lo, int n, int dir);
void compare(int i, int j, int dir);
void swap(int i, int j);

#define ASCENDING 1
#define DESCENDING 0


static int *a;
void sort(int *arr, int len) {
	a = arr;
	bitonicSort(0, len, ASCENDING);
}

void bitonicSort(int lo, int n, int dir) {
	// do nothing if n <= 1 (nothing to sort)
	if(n > 1) {
		int m = n/2;
		bitonicSort(lo, m, ASCENDING);
		bitonicSort(lo+m, m, DESCENDING);
		bitonicMerge(lo, n, dir);
	}
}

void bitonicMerge(int lo, int n, int dir) {
	if(n > 1) {
		int m = n/2;
		int i;
		for(i = lo; i < lo+m; i++)
			compare(i, i+m, dir);
		bitonicMerge(lo, m, dir);
		bitonicMerge(lo+m, m, dir);
	}
}

// Compare two different indices and swap based on current direction
void compare(int i, int j, int dir) {
	if(dir == (a[i]>a[j]))
		swap(i, j);
}


// Swap two indices in the array
void swap(int i, int j) {
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}
