#include <stdio.h>
#include <stdbool.h>
#include "Data.h"
#include "LinkedList.h"

int main(void) {
	List *list = make_list();
	bool err;
	for (int i = 0; i < 8; i++) {
		push(list, make_data(i + 10));
		print_list(list);
	}
	printf("%d\n", indexof(list, make_data(15)));
	set_data(list, 5, make_data(100));
	print_list(list);
	while (!empty_list(list)) {
		delete_final(list);
		print_list(list);
	}
	delete_list(list);
	return 0;
}