#ifndef _SORT_H_
#define _SORT_H_
#define DEBUG 0
void bitonic_sort(int* arr, const size_t len);
void bitonic_psort(int* arr, const size_t len, const int threads);

void radix_sort(int *a, const size_t len);
void radix_psort(int *a, const size_t len, const int threads);

void sample_sort(int *a, const size_t len, const int threads);

void merge_sort(int *a, const size_t len);
void two_way_merge(int *a, const size_t len);
void k_way_merge(int *a, int **arrs, const size_t len, int k);

void insertion_sort(int *a, const size_t len);
void rev_insertion_sort(int *a, const size_t len);


void qsort_wrapper(int *a, const size_t len);

#endif /* _SORT_H_ */
