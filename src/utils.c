#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"
#include "utils.h"
#ifndef SUNOS
#include "hrtimer_x86.h"
#endif
#include <time.h>
#include <sys/time.h>

void print_array(int *arr, int len) {
	int i;
	for(i = 0 ; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int validate_sort(int *arr, int *copy, int len) {
	int i;
	int ordered = 1;
	for(i = 0; i < len; i++) {
		if(arr[i] != copy[i]) {
			ordered = 0;
		}
	}
	return ordered;
}

void create_copy(int *copy, int *arr, int len) {
	int i; 
	for(i = 0; i < len; i++) {
		copy[i] = arr[i];
	}
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

/* Four calls to random then divide by four */
void create_gauss(int *a, int len) {
	int i;
	for(i = 0; i < len; i++) {
		a[i] = rand();
		a[i] += rand();
		a[i] += rand();
		a[i] += rand();
		a[i] /= 4;
	}
}

/* Fill the array with zeros */
void create_zero(int *a, int len) {
	int i;
	for(i = 0; i < len; i++) {
		a[i] = 0;
	}
}

void create_duplicates(int *a, int len) {
	int i;
	for(i = 0; i < len; i++) {
		a[i] = rand() % (len / 2);
	}

}

void run_psort_tests(void (*sortfunc)(int *, const size_t, const int),
		const char* name, int *arr, const size_t len, const int threads) {
	int *copy = (int *) calloc(len, sizeof(int));
	int *orig = (int *) calloc(len, sizeof(int));
	int i;
#ifndef SUNOS
	double start, end;
#else
	struct timeval start, end;
#endif
	if(verbose) {
		printf("========================\n");
		printf("%s Sort\n", name);
		printf("========================\n");
	}
	if(verbose) {
		/* Reverse array */
		printf("Reverse test\n");
	}
	create_reverse(orig, len);
	create_copy(copy, orig, len);
	double total = 0;
	radix_sort(copy, len);
	for(i = 0; i < ITER; i++) {
		create_copy(arr, orig, len);
#ifndef SUNOS
		start = gethrtime_x86();
#else
		gettimeofday(&start, NULL);
#endif
		sortfunc(arr, len, threads);
#ifndef SUNOS
		end = gethrtime_x86();
		double totaltime = end-start;
#else
		gettimeofday(&end, NULL);
		double totaltime = getTimeDouble(&start, &end);
#endif
		if(verbose) {
			printf("%i: %f\n", i, totaltime);
		}
		total += totaltime;
		assert(validate_sort(arr, copy, len) != 0);
	}
	if(verbose) {
		printf("Time: %f\n", total/(ITER * 1.0));
	}
	else {
		printf("%f, ", total/(ITER * 1.0));
	}

	/* Random array */
	if(verbose) {
		printf("Random test\n");
	}
	create_random(orig, len);
	create_copy(copy, orig, len);
	radix_sort(copy, len);
#ifndef SUNOS
	total = 0;
#endif
	for(i = 0; i < ITER; i++) {
		create_copy(arr, orig, len);
#ifndef SUNOS
		start = gethrtime_x86();
#else
		gettimeofday(&start, NULL);
#endif
		sortfunc(arr, len, threads);
#ifndef SUNOS
		end = gethrtime_x86();
		double totaltime = end-start;
#else
		gettimeofday(&end, NULL);
		double totaltime = getTimeDouble(&start, &end);
#endif
		if(verbose) {
			printf("%i: %f\n", i, totaltime);
		}
		total += totaltime;
		assert(validate_sort(arr, copy, len) != 0);
	}
	if(verbose) {
		printf("Time: %f\n", total/(ITER*1.0));
	}
	else {
		printf("%f, ", total/(ITER*1.0));
	}
	if(verbose) {
		printf("%s passed!\n", name);
		printf("------------------------\n");
	}
	free(orig);
	free(copy);
}

/* Sequential sort tests */
void run_sort_tests(void (*sortfunc)(int *, const size_t),
		const char* name, int *arr, const size_t len) {
	int *orig = (int *) calloc(len, sizeof(int));
	int *copy = (int *) calloc(len, sizeof(int));
	int i;
#ifndef SUNOS
	double start, end;
#else
	struct timeval start, end;
#endif
	if(verbose) {
		printf("========================\n");
		printf("%s Sort\n", name);
		printf("========================\n");
	}
	/* Reverse array */
	if(verbose) {
		printf("Reverse test\n");
	}
	create_reverse(orig, len);
	create_copy(copy, orig, len);
	radix_sort(copy, len);
	double total = 0;
	for(i = 0; i < ITER; i++) {
		create_copy(arr, orig, len);
#ifndef SUNOS
		start = gethrtime_x86();
#else
		gettimeofday(&start, NULL);
#endif
		sortfunc(arr, len);
#ifndef SUNOS
		end = gethrtime_x86();
		double totaltime = end-start;
#else
		gettimeofday(&end, NULL);
		double totaltime = getTimeDouble(&start, &end);
#endif
		if(verbose) {
			printf("%i: %f\n", i, totaltime);
		}
		total += totaltime;
		assert(validate_sort(arr, copy, len) != 0);
	}

	if(verbose) {
		printf("Time: %f\n", total/(ITER * 1.0));
	}
	else {
		printf("%f, ", total/(ITER * 1.0));
	}


	/* Random array */
	if(verbose) {
		printf("Random test\n");
	}
	create_random(orig, len);
	create_copy(copy, orig, len);
	radix_sort(copy, len);
	total = 0;
	for(i = 0; i < ITER; i++) {
		create_copy(arr, orig, len);
#ifndef SUNOS
		start = gethrtime_x86();
#else
		gettimeofday(&start, NULL);
#endif
		sortfunc(arr, len);
#ifndef SUNOS
		end = gethrtime_x86();
		double totaltime = end-start;
#else
		gettimeofday(&end, NULL);
		double totaltime = getTimeDouble(&start, &end);
#endif

		total += totaltime;
		if(verbose) {
			printf("%i: %f\n", i, totaltime);
		}
		assert(validate_sort(arr, copy, len) != 0);
	}
	if(verbose) {
		printf("Time: %f\n", total/(ITER*1.0));
	}
	else {
		printf("%f, ", total/(ITER*1.0));
	}

	if(verbose) {
		printf("%s passed!\n", name);
		printf("------------------------\n");
	}
	
	free(orig);
	free(copy);
}

double getTimeDouble(struct timeval *start, struct timeval *end) {
	double time = ((end->tv_sec * 1000000 + end->tv_usec) - (start->tv_sec * 1000000 + start->tv_usec)) / 1000000.0;
	return time;
}
