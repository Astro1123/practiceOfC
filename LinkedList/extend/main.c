#include <stdio.h>
#include "String.h"

int main(void) {
	String* s = makeString("Hello, ");
	addString(s, "world!");
	
	printf("%s\n", s->str);
	destroyString(s);
	return 0;
}