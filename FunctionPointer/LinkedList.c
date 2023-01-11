#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "sort.h"
#include "LinkedList.h"

Cell *make_cell(sortMethod val, Cell *cp) {
	Cell *cell = (Cell *)malloc(sizeof(Cell));
	if (cell != NULL) {
		cell->item = val;
		cell->next = cp;
	}
	return cell;
}

List *make_list(void) {
	List *list = (List *)malloc(sizeof(List));
	if (list != NULL) {
		list->top = make_cell(make_null_data(), NULL);
		if (list->top == NULL) {
			free(list);
			return NULL;
		}
	}
	return list;
}

void delete_cell(Cell *cp) {
	while (cp != NULL) {
		Cell *cell = cp->next;
		free(cp);
		cp = cell;
	}
}

void delete_list(List *list) {
	delete_cell(list->top);
	free(list);
}

Cell *final_cell(Cell *cp, Cell **before) {
	*before = NULL;
	while (cp->next != NULL) {
		*before = cp;
		cp = cp->next;
	}
	return cp;
}

sortMethod final(List *list, bool *err) {
	Cell *before;
	Cell *cp = final_cell(list->top, &before);
	if (cp == NULL) {
		*err = false;
		return make_null_data();
	}
	*err = true;
	return cp->item;
}

int get_size(List *list) {
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

Cell *nth_cell(Cell *cp, int n) {
	for (int i = -1; cp != NULL; i++, cp = cp->next)
		if (i == n) break;
	return cp;
}

sortMethod nth(List *list, int n, bool *err) {
	Cell *cp = nth_cell(list->top, n);
	if (cp == NULL) {
		*err = false;
		return make_null_data();
	}
	*err = true;
	return cp->item;
}

bool insert_final(List *list, sortMethod x) {
	Cell *before;
	Cell *cp = final_cell(list->top, &before);
	if (cp == NULL) return false;
	cp->next = make_cell(x, cp->next);
	return true;
}

bool insert_nth(List *list, int n, sortMethod x) {
	Cell *cp = nth_cell(list->top, n - 1);
	if (cp == NULL) return false;
	cp->next = make_cell(x, cp->next);
	return true;
}

bool push(List *list, sortMethod x) {
	return insert_nth(list, 0, x);
}

bool delete_final(List *list) {
	Cell *before;
	Cell *cp = final_cell(list->top, &before);
	if (before == NULL || cp == NULL) return false;
	before->next = NULL;
	free(cp);
	return true;
}

bool delete_nth(List *list, int n) {
	Cell *cp = nth_cell(list->top, n - 1);
	Cell *cell;
	if (cp == NULL || cp->next == NULL) return false;
	cell = cp->next;
	cp->next = cp->next->next;
	free(cell);
	return true;
}

bool set_data(List *list, int n, sortMethod x) {
	Cell *cp = nth_cell(list->top, n);
	if (cp == NULL) {
		return false;
	}
	cp->item = x;
	return true;
}

sortMethod pop(List *list, bool *err) {
	sortMethod x = first(list, err);
	if (*err) delete(list);
	return x;
}

int indexof(List *list, sortMethod x) {
	int i;
	int res = -1;
	bool err;
	for (i = 0; i < get_size(list); i++) {
		sortMethod d = nth(list, i, &err);
		if (compare_data(d, x)) {
			res = i;
			break;
		}
	}
	return res;
}

bool empty_list(List *list) {
	return list->top->next == NULL;
}

void print_list(List *list) {
	printf("( ");
	for (Cell *cp = list->top->next; cp != NULL; cp = cp->next)
		print_data(cp->item);
	printf(")\n");
}

void clear(List *list) {
	while (!empty_list(list)) {
		delete_final(list);
	}
}