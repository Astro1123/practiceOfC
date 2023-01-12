#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"

#define STR_SIZE 256

int getNum(bool *err) {
	char str[STR_SIZE];
	char *endptr;
	int res;
	
	if (getString(str, STR_SIZE) == FAILURE) {
		res = 0;
		*err = false;
	} else {
		res = (int)strtol(str, &endptr, 10);
		if (endptr[0] != '\0') {
			*err = false;
		} else {
			*err = true;
		}
	}
	return res;
}

int getStringStr(char *str, size_t size, char* s) {
	if (s) printf("%s", s);
	return getString(str, size);
}

int getString(char *str, size_t size) {
	int len;
	int res = FAILURE;
	
	if (str == NULL) return FAILURE;
    if (fgets(str, size, stdin) != NULL) {
    	len = strlen(str);
        if (str[len - 1] == '\n') {
            str[--len] = '\0';
        } else {
            while (getchar() != '\n') {}
        }
        res = len;
    }
    return res;
}