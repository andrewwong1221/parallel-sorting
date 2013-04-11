#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ARRAY_LENGTH 10
void sort(int *arr, int len);
int validate_sort(int *arr, int len);
void create_random(int *arr, int len);
void print_array(int *arr, int len);

int main(int argc, char *argv[]) {
	int len = ARRAY_LENGTH;
	int arr[ARRAY_LENGTH];
	create_random(arr, len);

	// Sort the array
	sort(arr, len);

	// Ensure the array is sorted
	printf("SORTED: %d\n", validate_sort(arr, len));
	return 0;
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
