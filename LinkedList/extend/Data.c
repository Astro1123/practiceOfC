#include "Data.h"

Data make_data(int i, char* s) {
	Data d;
	d.i = i;
	d.s = s;
	return d;
}