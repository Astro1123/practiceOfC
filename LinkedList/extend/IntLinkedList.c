#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "IntLinkedList.h"

#define Data int
#define NULL_DATA 0
#define Cell IntCell
#define List IntList

static void init(List *list);
static Cell *make_cell(Data val, Cell *cp);
static void delete_cell(Cell *cp);
static void delete_list(List *list);
static Cell *final_cell(Cell *cp, Cell **before);
static Data final(List *list, bool *err);
static Cell *nth_cell(Cell *cp, int n);
static Data nth(List *list, int n);
static Data _nth(List *list, int n, bool *err);
static bool insert_final(List *list, Data x);
static bool insert_nth(List *list, int n, Data x);
static bool push(List *list, Data x);
static bool delete_final(List *list);
static bool delete_nth(List *list, int n);
static Data pop(List *list);
static Data _pop(List *list, bool *err);
static bool empty_list(List *list);
static int get_size(List *list);
static void clear(List *list);
static int indexof(List *list, Data x);
static bool set_data(List *list, int n, Data x);
static Data make_null_data(void);
static Data make_data(int x);
static void print_list(List *list);
static inline void print_data(Data x);
static inline int compare_data(Data a, Data b);
static void set_print(List *list, void (*)(List*));
static void set_compare(List *list, int (*)(Data, Data));


List* make_int_list(void) {
	List *list = (List *)malloc(sizeof(List));
	if (list != NULL) {
		list->top = make_cell(make_null_data(), NULL);
		if (list->top == NULL) {
			free(list);
			return NULL;
		}
	}
	init(list);
	return list;
}

static inline void print_data(Data x) {
	printf("%d ", x);
}

static inline int compare_data(Data a, Data b) {
	return a == b;
}

static void init(List *list) {
	list->destroy = delete_list;
	list->push = push;
	list->add = insert_nth;
	list->enqueue = insert_final;
	list->set = set_data;
	list->delete = delete_nth;
	list->clear = clear;
	list->get = nth;
	list->pop = pop;
	list->dequeue = pop;
	list->isEmpty = empty_list;
	list->size = get_size;
	list->indexOf = indexof;
	list->printList = print_list;
	list->compare = compare_data;
	list->setPrint = set_print;
	list->setCompare = set_compare;
}

static Cell *make_cell(Data val, Cell *cp) {
	Cell *cell = (Cell *)malloc(sizeof(Cell));
	if (cell != NULL) {
		cell->item = val;
		cell->next = cp;
	}
	return cell;
}

static void delete_cell(Cell *cp) {
	while (cp != NULL) {
		Cell *cell = cp->next;
		free(cp);
		cp = cell;
	}
}

static void delete_list(List *list) {
	delete_cell(list->top);
	free(list);
}

static Cell *final_cell(Cell *cp, Cell **before) {
	*before = NULL;
	while (cp->next != NULL) {
		*before = cp;
		cp = cp->next;
	}
	return cp;
}

static Data final(List *list, bool *err) {
	Cell *before;
	Cell *cp = final_cell(list->top, &before);
	if (cp == NULL) {
		*err = false;
		return make_null_data();
	}
	*err = true;
	return cp->item;
}

static int get_size(List *list) {
	int i = 0;
	if (empty_list(list)) {
		return -1;
	}
	while (true) {
		Cell *cp = nth_cell(list->top, i++);
		if (!cp->next) break;
	}
	return i;
}

static Cell *nth_cell(Cell *cp, int n) {
	for (int i = -1; cp != NULL; i++, cp = cp->next)
		if (i == n) break;
	return cp;
}

static Data nth(List *list, int n) {
	Cell *cp = nth_cell(list->top, n);
	if (cp == NULL) {
		return make_null_data();
	}
	return cp->item;
}

static Data _nth(List *list, int n, bool *err) {
	Cell *cp = nth_cell(list->top, n);
	if (cp == NULL) {
		*err = false;
		return make_null_data();
	}
	*err = true;
	return cp->item;
}

static bool insert_final(List *list, Data x) {
	Cell *before;
	Cell *cp = final_cell(list->top, &before);
	if (cp == NULL) return false;
	cp->next = make_cell(x, cp->next);
	return true;
}

static bool insert_nth(List *list, int n, Data x) {
	Cell *cp = nth_cell(list->top, n - 1);
	if (cp == NULL) return false;
	cp->next = make_cell(x, cp->next);
	return true;
}

static bool push(List *list, Data x) {
	return insert_nth(list, 0, x);
}

static bool delete_final(List *list) {
	Cell *before;
	Cell *cp = final_cell(list->top, &before);
	if (before == NULL || cp == NULL) return false;
	before->next = NULL;
	free(cp);
	return true;
}

static bool delete_nth(List *list, int n) {
	Cell *cp = nth_cell(list->top, n - 1);
	Cell *cell;
	if (cp == NULL || cp->next == NULL) return false;
	cell = cp->next;
	cp->next = cp->next->next;
	free(cell);
	return true;
}

static bool set_data(List *list, int n, Data x) {
	Cell *cp = nth_cell(list->top, n);
	if (cp == NULL) {
		return false;
	}
	cp->item = x;
	return true;
}

static Data pop(List *list) {
	bool err;
	Data s = _pop(list, &err);
	if (!err) return make_null_data();
	return s;
}

static Data _pop(List *list, bool *err) {
	Data x = _nth(list, 0, err);
	if (*err) list->delete(list, 0);
	return x;
}

static int indexof(List *list, Data x) {
	int i;
	int res = -1;
	bool err;
	for (i = 0; i < get_size(list); i++) {
		Data d = nth(list, i);
		if (compare_data(d, x)) {
			res = i;
			break;
		}
	}
	return res;
}

static bool empty_list(List *list) {
	return list->top->next == NULL;
}

static void clear(List *list) {
	while (!empty_list(list)) {
		delete_final(list);
	}
}

static void print_list(List *list) {
	printf("( ");
	for (Cell *cp = list->top->next; cp != NULL; cp = cp->next)
		print_data(cp->item);
	printf(")\n");
}

static Data make_null_data(void) {
	return make_data(NULL_DATA);
}

static Data make_data(int x) {
	return x;
}

static void set_print(List *list, void (*print)(List*)) {
	list->printList = print;
}

static void set_compare(List *list, int (*compare)(Data, Data)) {
	list->compare = compare;
}