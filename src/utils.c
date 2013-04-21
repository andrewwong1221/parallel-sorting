#include <stdio.h>

void print_array(int *arr, int len) {
	int i;
	for(i = 0 ; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
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
