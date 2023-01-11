#ifndef STRUCT_H
#define STRUCT_H

typedef struct {
	const char* name;
	int code;
	int (*func)(int*, int);
} sortMethod;

typedef struct cell {
	sortMethod item;
	struct cell *next;
} Cell;

typedef struct {
	Cell *top;
} List;

#endif /* STRUCT_H */