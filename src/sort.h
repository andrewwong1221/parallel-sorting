#ifndef _SORT_H_
#define _SORT_H_
#define DEBUG 0
void bitonic_sort(int* arr, const size_t len);
void bitonic_psort(int* arr, const size_t len, const int threads);

void radix_sort(int *a, const size_t len);
void radix_psort(int *a, const size_t len, const int threads);

void sample_sort(int *a, const size_t len, const int threads);

void merge_sort(int *a, const size_t len);

#endif /* _SORT_H_ */
