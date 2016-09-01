#include "algorithms.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "harness.h"

#define NUM_ALGORITHMS 5

bool isSorted(int* arr, int len) {
	int prev = INT_MIN;
	for(int i = 0; i < len; i++) {
		if(prev > arr[i]) {
			return false;
		}
		prev = arr[i];
	}
	return true;
}

double timeFunction(void (*fn)(int *, int), int* arr, int len) {
	clock_t begin = clock();
	fn(arr, len);
	clock_t end = clock();
	return (double)(end - begin) / CLOCKS_PER_SEC;
}

int* generateArray(int len) {
	int* arr = (int*) malloc(len * sizeof(int));
	for(int i = 0; i < len; i++) {
		arr[i] = rand();
	}
	return arr;
}

void checkCorrectness(char* name, void (*fn)(int *, int), const int* sizes, int len) {
	bool passed = true;
	for(int i = 0; i < len / sizeof(int); i++) {
		int len = sizes[i];
		int* arr = generateArray(len);
		fn(arr, len);
		if(!isSorted(arr, len)) {
			passed = false;
		}
		free(arr);
	}
	if(passed) {
		printf("%s Sort: passed!\n", name);
	} else {
		printf("%s Sort failed at least one test case.\n", name);
	}
}

void evaluatePerformance(char* name, void (*fn)(int*, int), const int* sizes, int len) {
	printf("Testing %s Sort.\n", name);
	for(int i = 0; i < len / sizeof(int); i++) {
		int len = sizes[i];
		int* arr = generateArray(len);
		double t = timeFunction(fn, arr, len);
		printf("Array of length %d took %.3f seconds.\n", len, t);
		free(arr);
	}
	printf("\n");
}


int main(int argc, char** argv) {
	char* names[] = {"Selection", "Insertion", "Heap", "Merge", "Quick"};
	void (*algorithms[])(int*, int) =
		{selectionSort, insertionSort, heapSort, mergeSort, quickSort};
	int num_algs = 5;

	srand((unsigned) time(NULL));

	printf("\nBeginning tests for correctness.\n");
	printf("--------------------------------\n");
	const int c_sizes[] = {0, 1, 2, 3, 4, 5, 10, 100, 1000};
	for(int i = 0; i < num_algs; i++) {
		checkCorrectness(names[i], algorithms[i], c_sizes, sizeof(c_sizes));
	}

	printf("\nBeginning tests for performance.\n");
	printf("--------------------------------\n");
	const int p_sizes[] = {10, 100, 1000, 10000};
	for(int i = 0; i < num_algs; i++) {
		evaluatePerformance(names[i], algorithms[i], p_sizes, sizeof(p_sizes));
	}

	printf("Beginning tests for stress performance.\n");
	printf("--------------------------------\n");
	const int s_sizes[] = {100000, 1000000, 10000000};
	for(int i = 2; i < num_algs; i++) {
		evaluatePerformance(names[i], algorithms[i], s_sizes, sizeof(s_sizes));
	}

}
