#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "LinkedList.h"
#include "split.h"

#define iserr(cnd) ((cnd) < 0)

typedef struct {
	List* list;
	int count;
	int length;
} splitStruct;

static splitStruct ss;

int splitInit(char* str, const char* delim) {
	ss.list = make_list();
	ss.count = 0;
	ss.length = split(str, delim, ss.list);
	return ss.length;
}

char* splitNext(int* status) {
	char* str;
	if (ss.count >= ss.length) {
		if (status) {
			*status = OUTPUT_FAILURE;
		}
		return NULL;
	}
	str = ss.list->dequeue(ss.list);
	ss.count++;
	if (status) {
		if (ss.count == ss.length) {
			*status = STRING_END;
		} else {
			*status = SUCCESS;
		}
	}
	return str;
}

int split(char* str, const char* delim, List* list) {
	int status;
	char* s;
	int cnt = 0;
	
	if (delim == NULL || list == NULL) return SPLIT_FAILURE;
	s = _split(str, delim, &status);
	if (!iserr(status)) {
		list->enqueue(list, s);
		cnt++;
	} else {
		return SPLIT_FAILURE;
	}
	
	while (status == SUCCESS) {
		s = _split(NULL, delim, &status);
		if (!iserr(status)) {
			list->enqueue(list, s);
			cnt++;
		} else {
			return SPLIT_FAILURE;
		}
	}
	return cnt;
}

char* strtok_m(char* str, const char* delim) {
	int status;
	return _split(str, delim, &status);
}

char* _split(char* str, const char* delim, int *status) {
	static char* s;
	static size_t len;
	char *s1, *res;

	if (status == NULL) return NULL;
	if (delim == NULL) {
		*status = NULL_POINTER_ERR;
		return s;
	}
	*status = SUCCESS;
	if (str != NULL) {
		s = str;
		len = strlen(str);
	}
	res = s;
	for (; *s; s++, len--) {
		for (s1 = (char *) delim; *s1; s1++) {
			if (*s1 == *s) {
				*s = '\0';
				s++;
				len--;
				goto endLoop;
			}
		}
	}
endLoop:
	if (len == 0) *status = STRING_END;
	return res;
}
