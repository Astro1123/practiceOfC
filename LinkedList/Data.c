#include <stdio.h>
#include <stdbool.h>
#include "Data.h"

Data make_data(int i) {
	Data d;
	d.i = i;
	return d;
}

Data make_null_data(void) {
	return make_data(0);
}

void print_data(Data data) {
	printf("%d ", data.i);
}

bool compare_data(Data data1, Data data2) {
	bool res = true;
	res &= (data1.i == data2.i);
	return res;
}