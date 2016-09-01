#include "algorithms.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "harness.h"

#define SIZE 100000

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

int main(int argc, char** argv) {
	int array_size;
	if(argc == 1) {
		array_size = SIZE;
	} else if(argc == 2) {
		array_size = atoi(argv[1]);
	} else {
		printf("There are too many command line arguments.\n");
		exit(1);
	}

	srand((unsigned) time(NULL));
	int* arr = (int*) malloc(array_size * sizeof(int));
	for(int i = 0; i < array_size; i++) {
		arr[i] = rand() % 30;
	}

	// insertionSort(arr, array_size);
	// selectionSort(arr, array_size);
	// heapSort(arr, array_size);
	// mergeSort(arr, array_size);
	// quickSort(arr, array_size);
	printf("The array was %d sorted\n", isSorted(arr, array_size));

	free(arr);
}
