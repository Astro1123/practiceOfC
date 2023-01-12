#include <stdio.h>
#include <stdbool.h>
#include "Data.h"
#include "LinkedList.h"

int main(void) {
	List *list = make_list();
	bool err;
	for (int i = 0; i < 8; i++) {
		list->push(list, make_data(i + 10));
		print_list(list);
	}
	printf("%d\n", list->indexOf(list, make_data(15)));
	list->set(list, 5, make_data(100));
	print_list(list);
	while (!list->isEmpty(list)) {
		list->delete(list, list->size(list) - 1);
		print_list(list);
	}
	list->destroy(list);
	return 0;
}