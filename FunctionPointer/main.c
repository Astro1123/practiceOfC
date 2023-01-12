#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "struct.h"
#include "sort.h"
#include "LinkedList.h"

#define FAILURE -1

#define ERR_POINTER_NULL -2
#define ERR_INVALID_VALUE -1
#define SUCCESS 0

#define STR_SIZE 256
#define ARRAY_SIZE 100

enum select {
	CONTINUE,
	QUIT
};

int getString(char*, size_t);
int getNum(bool*);
int input(char*, int, int);
int shuffle(int*, int);
void printArray(int*, int);
void printName(List*, int);
void makeArray(int*, int);
void printOrderName(void);

int main(void) {
	int array[ARRAY_SIZE];
	int i;
	int method;
	int len;
	int res;
	OrderType order;
	sortMethod sortmet;
	List* list;
	char SelectContinueStr[STR_SIZE];
	
	srand((unsigned int)time(NULL));
	
	list = initMethod();
	len = list->size(list);
	
	snprintf(SelectContinueStr, STR_SIZE, "Select continue (Continue: %d, Quit: %d) : ", CONTINUE, QUIT);
	
	do {
		makeArray(array, ARRAY_SIZE);
		
		printf("Array:\n");
		printArray(array, ARRAY_SIZE);
		printf("\n");
		
		printf("Method:\n");
		printName(list, len);
		printf("\n");
		
		method = input("Select method : ", 0, len);
		sortmet = list->get(list, method);
		printf("\n");
		
		printf("Order:\n");
		printOrderName();
		printf("\n");
		
		order = input("Select order : ", ASCENDING, DESCENDING);
		orderSelect(order);
		printf("\n");
		
		res = sortmet.func(array, ARRAY_SIZE);
		if (res == SORT_SUCCESS) {
			printf("Sort Completed!:\n");
			printf("\n");
			
			printf("Array:\n");
			printArray(array, ARRAY_SIZE);
			printf("\n");
		}
	} while (input(SelectContinueStr, CONTINUE, QUIT) == CONTINUE);
}

void printName(List* list, int len) {
	int i;
	sortMethod sortmet;
	for (i = 0; i < len; i++) {
		sortmet = list->get(list, i);
		printf("\t%s (%d)\n", sortmet.name, i);
	}
}

void printArray(int *array, int size) {
	int i;
	printf("array : { ");
	for (i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("}\n");
}

void printOrderName(void) {
	printf("Ascending order: %d\nDescending order: %d\n", ASCENDING, DESCENDING);
}

void makeArray(int *array, int size) {
	int i;
	for (i = 0; i < size; i++) {
		array[i] = i + 1;
	}
	shuffle(array, ARRAY_SIZE);
}

int shuffle(int* num, int size) {
	int i, r, tmp;
	
	if (size < 1) return ERR_INVALID_VALUE;
	if (num == NULL) return ERR_POINTER_NULL;
	
	i = size;
	while (i > 1) {
		r = rand() % i;
		i--;
		tmp = num[i];
		num[i] = num[r];
		num[r] = tmp;
	}
	return SUCCESS;
}

int input(char *str, int min, int max) {
	bool err;
	int res;
	
	do {
		if (str) printf("%s", str);
		res = getNum(&err);
		if (res < min || res > max) res = FAILURE;
		if (!err) res = FAILURE;
	} while (res == FAILURE);
	
	return res;
}

int getNum(bool *err) {
	char str[STR_SIZE];
	char *endptr;
	int res;
	
	if (getString(str, STR_SIZE) == FAILURE) {
		res = 0;
		*err = false;
	} else {
		res = (int)strtol(str, &endptr, 10);
		if (endptr[0] != '\0') {
			*err = false;
		} else {
			*err = true;
		}
	}
	return res;
}

int getString(char *str, size_t size) {
	int len;
	int res = FAILURE;
	
	if (str == NULL) return FAILURE;
    if (fgets(str, size, stdin) != NULL) {
    	len = strlen(str);
        if (str[len - 1] == '\n') {
            str[--len] = '\0';
        } else {
            while (getchar() != '\n') {}
        }
        res = len;
    }
    return res;
}