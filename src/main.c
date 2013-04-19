#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "sort.h"

#define ARRAY_LENGTH 16
int validate_sort(int *arr, int len);
void create_reverse(int *arr, int len);
void create_random(int *arr, int len);
void print_array(int *arr, int len);

int verbose = 0;
int nthreads = 1;
double start, end;

void usage() {
	printf("prog [-s <arraysize>] [-n <threads>]\n");
	exit(1);
}

extern char *optarg;
int main(int argc, char *argv[]) {
	int len = ARRAY_LENGTH;
	int *arr;
	int i;
	while((i = getopt(argc, argv, "s:n:v")) != -1) {
		switch(i) {
			case 's':
				// Fix this later
				len = atoi(optarg);
				if(len < 1)
					usage();
				break;
			case 'n':
				// Set number of threads
				nthreads = atoi(optarg);
				// Currently assumes the user isn't stupid
				if(nthreads < 1)
					usage();
				break;
			case 'v':
				verbose = 1;
				break;
			default:
				usage();
				break;
		}
	}
	printf("len=%d\n", len);
	arr = (int *)malloc(sizeof(int) * len);
	create_reverse(arr, len);
	// Sort the array
	bitonic_psort(arr, len, nthreads);
	// print_array(arr,len);
	printf("SORTED: %d\n", validate_sort(arr, len));

	// create_random(arr, len);
	// psort(arr, len, nthreads);

	// // Ensure the array is sorted
	// printf("SORTED: %d\n", validate_sort(arr, len));
	return 0;
}
void create_reverse(int *arr, int len) {
	int i;
	for(i = 0; i < len; i++) {
		arr[i] = len - i;
	}

}

void create_random(int *arr, int len) { 
	int i;
	for(i = 0; i < len; i++)
		arr[i] = rand();
}

int validate_sort(int *arr, int len) {
	int i;
	int order = 1;
	for(i = 1; i < len; i++) {
		if(arr[i-1] > arr[i]) {
			order = 0;
		}
	}
	return order;
}

void print_array(int *arr, int len) {
	int i;
	for(i = 0 ; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

double get_time() {
	return end-start;
}
