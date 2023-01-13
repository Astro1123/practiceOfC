#include <stdio.h>
#include <stdlib.h>
#include "CharLinkedList.h"
#include "String.h"

static void make(String* s);

String* makeString(const char* sp) {
	String* str = (String *)malloc(sizeof(String));
	char* s = (char *) sp;
	
	str->strdata = make_char_list();
	while (*s) {
		ListEnqueue(str->strdata, *(s++));
	}
	make(str);
	return str;
}

void setString(String* str, const char* sp) {
	char* s = (char *) sp;
	
	str->strdata = make_char_list();
	while (*s) {
		ListEnqueue(str->strdata, *(s++));
	}
	free(str->str);
	make(str);
}

void addString(String* str, const char* sp) {
	char* s = (char *) sp;
	
	while (*s) {
		ListEnqueue(str->strdata, *(s++));
	}
	free(str->str);
	make(str);
}

void clearString(String* str) {
	ListClear(str->strdata);
	free(str->str);
	make(str);
}

void destroyString(String* str) {
	ListDestroy(str->strdata);
	free(str->str);
	free(str);
}

static void make(String* str) {
	int len, i;
	
	len = ListSize(str->strdata) + 1;
	str->str = (char *)malloc(sizeof(char) * (len + 1));
	for (i = 0; i < len; i++) {
		str->str[i] = ListGet(str->strdata, i);
	}
	str->str[len - 1] = '\0';
}