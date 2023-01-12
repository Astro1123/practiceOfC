#ifndef SPLIT_H
#define SPLIT_H

#include "struct.h"
#include "LinkedList.h"

#define SPLIT_FAILURE -1
#define OUTPUT_FAILURE -2

#define NULL_POINTER_ERR -1
#define SUCCESS 0
#define STRING_END 1

int splitInit(char* str, const char* delim);
char* splitNext(int* status);
int split(char*, const char*, List*);
char* strtok_m(char*, const char*);
char* _split(char*, const char*, int*);

#endif /* SPLIT_H */