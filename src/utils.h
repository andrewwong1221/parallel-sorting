#ifndef _UTILS_H_
#define _UTILS_H_
#define ITER 10

void print_array(int *a, int n);
int validate_sort(int *arr, int *copy, int len);
void create_reverse(int *arr, int len);
void create_random(int *arr, int len);
void run_sort_tests(void (*sortfunc)(int *, const size_t),
		const char* name, int *arr, const size_t len);
void run_psort_tests(void (*sortfunc)(int *, const size_t, const int),
		const char* name, int *arr, const size_t len, const int threads);

#endif /* _UTILS_H_ */
