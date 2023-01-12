#include <stdio.h>
#include "split.h"
#include "input.h"

#define STR_SIZE 256

int main(void) {
	char str[STR_SIZE];
	int status;
	char* s;
	
	getStringStr(str, STR_SIZE, "input: ");
	
	splitInit(str, ", ");
	do {
		printf("%s\n", splitNext(&status));
	} while (status == SUCCESS);
	
	return 0;
}