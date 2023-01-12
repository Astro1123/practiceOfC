#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#define FAILURE -1

int getNum(bool *err);
int getString(char *str, size_t size);
int getStringStr(char *str, size_t size, char* s);

#endif /* INPUT_H */