#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct cell {
	Data item;
	struct cell *next;
} Cell;

typedef struct {
	Cell *top;
} List;

#define add_final(list, d) insert_final(list, d)
#define add_index(list, d, index) insert_nth(list, index, d)
#define add(list, d) push(list, d)
#define enqueue(list, d) add_final(list, d)
#define dequeue(list, err) pop(list, err)
#define delete(list) delete_nth(list, 0)
#define first(list, err) nth(list, 0, err)

void print_list(List *list);
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
int get_size(List *list);
void clear(List *list);
int indexof(List *list, Data x);
bool set_data(List *list, int n, Data x);

#endif /* LINKEDLIST_H */