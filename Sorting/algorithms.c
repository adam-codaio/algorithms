#include "algorithms.h"

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
		int temp = arr[i];
		arr[i] = min;
		arr[idx] = temp;
	}
}

void swap(int* heap, int i, int j) {
	int temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

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

void buildHeap(int* heap, int* arr, int len) {
	int empty = 0;
	for(int i = 0; i < len; i++) {
		heap[empty] = arr[i];
		bubbleUp(heap, empty);
		empty += 1;
	}

}

void bubbleDown(int* heap, int bound) {
	int idx = 0;
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

void sort(int* heap, int len) {
	int unsorted = len - 1;
	while(unsorted > 0) {
		swap(heap, 0, unsorted);
		unsorted--;
		bubbleDown(heap, unsorted);
	}
}

void printArray(int* arr, int len) {
	for(int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void heapSort(int** arr, int len) {
	int* heap = malloc(len * sizeof(int));
	buildHeap(heap, *arr, len);
	sort(heap, len);
	free(*arr);
	*arr = heap;
}



