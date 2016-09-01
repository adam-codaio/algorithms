#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "algorithms.h"

/*
 * Implements Print Array.
 * ---------------------------------------------
 * Debugging function to print the elements of 
 * an array.
 */

void printArray(int* arr, int len) {
	for(int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/*
 * Implements Copy.
 * ---------------------------------------------
 * Copy takes the elements of one array and
 * copies them into another. Necessary for some
 * out of place algorithms.
 */

void copy(int* in, int* out, int len) {
	for(int i = 0; i < len; i++) {
		out[i] = in[i];
	}
}

/*
 * Implements In Place Swap.
 * ---------------------------------------------
 * Helper function to swap the elements at two
 * indices in the provided array.
 */

void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/*
 * Implements Out of Place Swap.
 * ---------------------------------------------
 * Helper function to swap an element in an 
 * input array to an output array and vice versa.
 */

void outSwap(int* in, int* out, int i, int j) {
	out[j] = in[i];
	in[i] = in[j];
}

/*
 * Implements Bubble Up.
 * ---------------------------------------------
 * Helper used in Build Max Heap. Takes a heap
 * and an index and repeatedly bubbles up the 
 * contents of the index until the heap property
 * is preserved. 
 */

void bubbleUp(int* heap, int idx) {
	while(idx > 0) {
		if((idx % 2) && (heap[idx / 2] < heap[idx])) {
			swap(heap, idx, idx / 2);
			idx = idx / 2;
		} else if(!(idx % 2) && heap[(idx - 1) / 2] < heap[idx]) {
			swap(heap, idx, (idx - 1) / 2);
			idx = (idx - 1) / 2;
		} else {
			break;
		}
	}
}

/*
 * Implements Build Max Heap.
 * ---------------------------------------------
 * Loops over the array and adds each element to
 * a binary heap. Appends element to end of heap
 * and then calls the bubble up helper.
 */

void buildMaxHeap(int* heap, int* arr, int len) {
	int empty = 0;
	for(int i = 0; i < len; i++) {
		heap[empty] = arr[i];
		bubbleUp(heap, empty);
		empty += 1;
	}
}

/*
 * Implements Bubble Down.
 * ---------------------------------------------
 * Helper used in Heap Sort. Takes a heap, an
 * index, and a bound and repeatedly bubbles 
 * down the contents of the provided index until
 * the heap property is preserved. 
 */

void bubbleDown(int* heap, int idx, int bound) {
	while((2 * idx + 1) <= bound) {
		int left = heap[2 * idx + 1];
		if((2 * idx + 2) <= bound) {
			int right = heap[2 * idx + 2];
			if(heap[idx] > left && heap[idx] > right) return;
			int max_idx = left > right ? 2 * idx + 1 : 2 * idx + 2;
			swap(heap, idx, max_idx);
			idx = max_idx;
		} else {
			if(heap[idx] > left) return;
			swap(heap, idx, 2 * idx + 1);
			idx = 2 * idx + 1;
		}
	}
}

/*
 * Implements Heap Sort.
 * ---------------------------------------------
 * Creates a binary max heap from the provided
 * array. Then repeatedly swaps the root to the
 * last element and bubbles down to preserve the
 * heap property.
 */

void heapSort(int* arr, int len) {
	int* heap = malloc(len * sizeof(int));
	buildMaxHeap(heap, arr, len);
	int unsorted = len - 1;
	while(unsorted >= 0) {
		outSwap(heap, arr, 0, unsorted);
		unsorted--;
		bubbleDown(heap, 0, unsorted);
	}
	free(heap);
}

/*
 * Implements Insertion Sort.
 * ---------------------------------------------
 * Loops over the array growing a list of sorted 
 * elements. For each element which has not been 
 * inserted, find its proper location, shift all
 * greater elements down, and insert.
 */

void insertionSort(int* arr, int len) {
	for(int i = 1; i < len; i++) {
		int temp = arr[i];
		for(int j = i - 1; j >= 0; j--) {
			if(temp > arr[j]) {
				if(j == i - 1) break;
				for(int k = i; k >= j + 2; k--) {
					arr[k] = arr[k - 1];
				}
				arr[j + 1] = temp;
				break;
			} else if(j == 0) {
				for(int k = i; k >= j + 1; k--) {
					arr[k] = arr[k - 1];
				}
				arr[j] = temp;
			}
		}
	}
}

/*
 * Implements Insertion Sort.
 * ---------------------------------------------
 * Loops over the array growing a list of sorted 
 * elements. Always finds the smallest remaining
 * element and swaps to append to the end of the
 * sorted segment.
 */

void selectionSort(int* arr, int len) {
	for(int i = 0; i < len; i++) {
		int idx = i;
		int min = arr[i];
		for(int j = i + 1; j < len; j++) {
			if(arr[j] < min) {
				min = arr[j];
				idx = j;
			}
		}
		swap(arr, i, idx);
	}
}

/*
 * Implements Merge.
 * ---------------------------------------------
 * The function that does the heavy lifting in
 * merge sort. This function merges all lists of 
 * length n of arr.
 */

void merge(int** arr, int** workspace, int n, int len) {
	int s = 0, t = 0;
	int u = n, v = n;
	for(int w = 0; w < len; ) {
		while(true) {
			if((v - u) == n || v >= len) {
				for(int i = t; i < (s + n); i++) {
					if(w == len) break;
					(*workspace)[w] = (*arr)[i];
					w++;
				}
				break;
			} else if ((t - s) == n) {
				for(int i = v; i < (u + n); i++) {
					if(w == len) break;
					(*workspace)[w] = (*arr)[i];
					w++;
				}
				break;
			} else if((*arr)[t] <= (*arr)[v]) {
				(*workspace)[w] = (*arr)[t];
				t++;
				w++;
			} else {
				(*workspace)[w] = (*arr)[v];
				v++;
				w++;
			}
		}
		s = s + 2 * n;
		t = s;
		u = u + 2 * n;
		v = u;
	}
	int* temp = *arr;
	*arr = *workspace;
	*workspace = temp;
}


/*
 * Implements Merge Sort.
 * ---------------------------------------------
 * Performs a bottom up merge sort. Starting 
 * with n lists of length 1, we repeatedly merge
 * into sorted lists of double the length until
 * we have a single sorted list.
 */

void mergeSort(int* arr, int len) {
	int* orig = arr;
	int* workspace = malloc(len * sizeof(int));
	int n = 1;
	while(n < len) {
		merge(&arr, &workspace, n, len);
		n *= 2;
	}
	// This is necessary if the final array ends up in the 
	// memory allocated to workspace
	if(orig != arr) {
		copy(arr, orig, len);
		free(arr);
	} else {
		free(workspace);
	}
}

/*
 * Implements Median of Three Partition Selection.
 * ---------------------------------------------
 * Looks at the first, middle, and last elements
 * of the array, chooses the median and returns
 * the index.
 */

int choosePartition(int* arr, int len) {
	int first, middle, last;
	first = arr[0];
	middle = arr[len / 2];
	last = arr[len - 1];
	if(middle >= first && middle <= last) return len / 2;
	if(middle >= last && middle <= first) return len / 2;
	if(first >= middle && first <= last) return 0;
	if(first >= last && first <= middle) return 0;
	return len - 1;
}

/*
 * Implements Quick Sort.
 * ---------------------------------------------
 * Uses Median of Three for selection partition.
 * Put all elements less than the partition to 
 * one side of the array and all elements to the
 * other side. Then recursively sort the halfs.
 */

void quickSort(int* arr, int len) {
	if(len <= 1) return;
	int partition = choosePartition(arr, len);
	int value = arr[partition];
	swap(arr, partition, len - 1);
	int min = 0, max = len - 2;
	while(true) {
		if(min > max) break;
		if(arr[min] < value) {
			min++;
		} else {
			swap(arr, min, max);
			max--;
		}
	}
	swap(arr, max + 1, len - 1);
	quickSort(arr, max + 1);
	quickSort(arr + (max + 2), len - (max + 2));
}







