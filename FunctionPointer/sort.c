#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "sort.h"
#include "LinkedList.h"

static int order;
static int* temp;

static sortMethod makeSortMethod(const char*, int (*)(int*, int));
static int BubbleSort(int*, int);
static int SelectionSort(int*, int);
static int InsertionSort(int*, int);
static int QuickSort(int* array, int size);
static void _QuickSort(int* array, int left, int right);
static int MergeSort(int* array, int size);
static void _MergeSort(int* array, int left, int right);

List* initMethod() {
	List* list = make_list();
	order = ASCENDING;
	
	add(list, makeSortMethod("Bubble Sort", BubbleSort));
	add(list, makeSortMethod("Selection Sort", SelectionSort));
	add(list, makeSortMethod("Insertion Sort", InsertionSort));
	add(list, makeSortMethod("Quick Sort", QuickSort));
	add(list, makeSortMethod("Merge Sort", MergeSort));
	
	return list;
}

static sortMethod makeSortMethod(const char* name, int (*func)(int* ,int)) {
	static int cnt = 0;
	sortMethod sort;
	
	sort.code = cnt++;
	sort.name = name;
	sort.func = func;
	
	return sort;
}

void print_data(sortMethod data) {
	printf("%s ", data.name);
}

void deleteMethod(List *list) {
	delete_list(list);
}

sortMethod make_null_data(void) {
	sortMethod sort;
	
	sort.code = -1;
	sort.name = NULL;
	sort.func = NULL;
	
	return sort;
}

int compare_data(sortMethod s1, sortMethod s2) {
	return (s1.code == s2.code);
}

void orderSelect(OrderType o) {
	order = o;
}

static int comp(int i, int j) {
	switch (order) {
		case DESCENDING:
			return i > j;
		default:
			return i < j;
	}
}

static void swap(int* i, int* j) {
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

static int BubbleSort(int* array, int size) {
	int i, j;
	
	for (i = 0; i < size - 1; i++) {
		for (j = 1; j < size - i; j++) {
			if (comp(array[j], array[j - 1])) {
				swap(&array[j], &array[j - 1]);
			}
		}
	}
	return SORT_SUCCESS;
}

static int SelectionSort(int* array, int size) {
	int i, j, tmp;
	
	for (i = 0; i < size; i++) {
		tmp = i;
		for (j = i + 1; j < size; j++) {
			if (comp(array[j], array[tmp])) {
				tmp = j;
			}
		}
		swap(&array[i], &array[tmp]);
	}
	return SORT_SUCCESS;
}

static int InsertionSort(int* array, int size) {
	int i, j, tmp;
	
	for (i = 1; i < size; i++) {
		if (comp(array[i], array[i - 1])) {
			j = i;
			tmp = array[i];
			do {
				array[j] = array[j - 1];
				j--;
			} while (j > 0 && comp(tmp, array[j - 1]));
			array[j] = tmp;
		}
	}
	return SORT_SUCCESS;
}

static int QuickSort(int* array, int size) {
	_QuickSort(array, 0, size - 1);
	return SORT_SUCCESS;
}

static void _QuickSort(int* array, int left, int right) {
	int i, j;
	int pivot;

	i = left;
	j = right;
	pivot = array[(left + right) / 2];
	
	while (true) {	
		while (comp(array[i], pivot)) {
			i++;
		}
		while (comp(pivot, array[j])) {
			j--;
		}
		if (i >= j) break;

		swap(&array[i], &array[j]);
		i++;
		j--;
	}

	if (left < i - 1) {
		_QuickSort(array, left, i - 1);	
	}
	if (j + 1 <  right) {
		_QuickSort(array, j + 1, right);
	}
}

static int MergeSort(int* array, int size) {
	temp = (int *)malloc(sizeof(int) * size);
	_MergeSort(array, 0, size - 1);
	free(temp);
	return SORT_SUCCESS;
}

static void _MergeSort(int* array, int left, int right) {
	int mid, i, j, k;
	
	if (left >= right)	return;

	mid = (left + right) / 2;
	_MergeSort(array, left, mid);
	_MergeSort(array, mid + 1, right);

	for (i = left; i <= mid; i++) {
		temp[i] = array[i];
	}

	for (i = mid + 1, j = right; i <= right; i++, j--) {
		temp[i] = array[j];
	}

	i = left;
	j = right;
	
	for (k = left; k <= right; k++) {
		if (comp(temp[i], temp[j])) {
			array[k] = temp[i++];
		} else {
			array[k] = temp[j--];
		}
	}
}