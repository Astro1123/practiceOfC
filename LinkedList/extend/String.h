#ifndef STRING_H
#define STRING_H

#include "CharLinkedList.h"

typedef struct {
	CharList* strdata;
	char* str;
} String;

String* makeString(const char* s);
void setString(String* str, const char* s);
void addString(String* str, const char* s);
void clearString(String* str);
void destroyString(String* str);

#endif /* STRING_H */