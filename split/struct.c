#include <stdio.h>
#include <string.h>

void print_data(char *s) {
	printf("%s ", s);
}

char* make_null_data(void) {
	return NULL;
}

int compare_data(char* s1, char* s2) {
	return (strcmp(s1, s2) == 0);
}