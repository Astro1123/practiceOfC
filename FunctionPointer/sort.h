#ifndef SORT_H
#define SORT_H

#define SORT_SUCCESS 0
#define SORT_FAILURE -1

typedef enum {
	ASCENDING,
	DESCENDING
} OrderType;

List* initMethod();
void deleteMethod(List*);
int compare_data(sortMethod, sortMethod);
sortMethod make_null_data(void);
void print_data(sortMethod data);
void orderSelect(OrderType);

#endif /* SORT_H */