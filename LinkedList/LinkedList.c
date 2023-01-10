#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int i;
} Data;

typedef struct cell {
	Data item;
	struct cell *next;
} Cell;

typedef struct {
	Cell *top;
} List;

Data make_data(int i);
Cell *make_cell(Data val, Cell *cp);
List *make_list(void);
void delete_cell(Cell *cp);
void delete_list(List *list);
Cell *final_cell(Cell *cp, Cell **before);
Data final(List *list, bool *err);
Cell *nth_cell(Cell *cp, int n);
Data nth(List *list, int n, bool *err);
bool insert_final(List *list, Data x);
bool insert_nth(List *list, int n, Data x);
bool push(List *list, Data x);
bool delete_final(List *list);
bool delete_nth(List *list, int n);
Data pop(List *list, bool *err);
bool empty_list(List *list);
void print_list(List *list);
int size(List *list);

Data make_data(int i) {
	Data d;
	d.i = i;
	return d;
}

Cell *make_cell(Data val, Cell *cp) {
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
		list->top = make_cell(make_data(0), NULL);
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

Data final(List *list, bool *err) {
	Cell *before;
	Cell *cp = final_cell(list->top, &before);
	if (cp == NULL) {
		*err = false;
		return make_data(0);
	}
	*err = true;
	return cp->item;
}

int size(List *list) {
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

Data nth(List *list, int n, bool *err) {
	Cell *cp = nth_cell(list->top, n);
	if (cp == NULL) {
		*err = false;
		return make_data(0);
	}
	*err = true;
	return cp->item;
}

bool insert_final(List *list, Data x) {
	Cell *before;
	Cell *cp = final_cell(list->top, &before);
	if (cp == NULL) return false;
	cp->next = make_cell(x, cp->next);
	return true;
}

bool insert_nth(List *list, int n, Data x) {
	Cell *cp = nth_cell(list->top, n - 1);
	if (cp == NULL) return false;
	cp->next = make_cell(x, cp->next);
	return true;
}

bool push(List *list, Data x) {
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

Data pop(List *list, bool *err) {
	Data x = nth(list, 0, err);
	if (*err) delete_nth(list, 0);
	return x;
}

bool empty_list(List *list) {
	return list->top->next == NULL;
}

void print_list(List *list) {
	printf("( ");
	for (Cell *cp = list->top->next; cp != NULL; cp = cp->next)
		printf("%d ", cp->item.i);
	printf(")\n");
}

int main(void) {
	List *list = make_list();
	bool err;
	for (int i = 0; i < 8; i++) {
		push(list, make_data(i + 10));
		print_list(list);
	}
	while (!empty_list(list)) {
		delete_final(list);
		print_list(list);
	}
	delete_list(list);
	return 0;
}