#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define STR_SIZE    (256)
#define FAILURE      (-1)

typedef enum {
	NO_INPUTSTR,
	ADD_INPUTSTR
} inputType;

#define size(v) sizeof(v) / sizeof(v[0])
#define SELECT(e1,e2,e3,func,...) func
#define getString(...) SELECT(__VA_ARGS__, _getStringStr, _getString) (__VA_ARGS__)

typedef struct {
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
	unsigned char b8 : 1;
} bitStruct_s1;

typedef struct {
	unsigned char b1 : 2;
	unsigned char b2 : 2;
	unsigned char b3 : 2;
	unsigned char b4 : 2;
} bitStruct_s2;

typedef struct {
	unsigned char b1 : 4;
	unsigned char b2 : 4;
} bitStruct_s4;

typedef union {
	unsigned char num;
	bitStruct_s1 s1;
	bitStruct_s2 s2;
	bitStruct_s4 s4;
} bit;

int _getString(char *str, int size);
int _getStringStr(char *str, int size, char *s);
unsigned char getNum(inputType type, ...);
unsigned char convert(char* str);
void print(bit b, int n);
const char *removeZero(const char *str);

int _getString(char *str, int size) {
	if (str == NULL) return FAILURE;
	int len;
    if (fgets(str, size, stdin) != NULL) {
    	len = strlen(str);
        if (str[len - 1] == '\n') {
            str[--len] = '\0';
        } else {
            while (getchar() != '\n') {}
        }
        return len;
    }
    return FAILURE;
}

int _getStringStr(char *str, int size, char *s) {
	if (s != NULL) {
		printf("%s", s);
	} else {
		printf("->");
	}
	return _getString(str, size);
}

unsigned char getNum(inputType type, ...) {
	char str[STR_SIZE];
	va_list va;
	
	if (type == NO_INPUTSTR) {
		getString(str, STR_SIZE);
	} else {
		va_start(va,type);
		getString(str, STR_SIZE, va_arg(va,char*));
		va_end(va);
	}
	return convert(str);
}

unsigned char convert(char* str) {
	if (str == NULL) return 0;
	if (str[0] == '0') {
		int len = strlen(str);
		if (len >= 2 && (str[1] >= '1' && str[1] <= '7')) {
			return strtol(str, NULL, 8);
		} else if (len >= 3) {
			if (str[1] == 'x' || str[1] == 'X') {
				return strtol(str, NULL, 16);
			} else if (str[1] == 'b') {
				return strtol(str + 2, NULL, 2);
			}
			return strtol(str, NULL, 10);
		} else {
			return strtol(str, NULL, 10);
		}
	} else {
		return strtol(str, NULL, 10);
	}
}

void print(bit b, int n) {
	char str[STR_SIZE];
	switch (n) {
		case 2:
			snprintf(str, STR_SIZE, "%d%d%d%d%d%d%d%d", b.s1.b8, b.s1.b7, b.s1.b6, b.s1.b5, b.s1.b4, b.s1.b3, b.s1.b2, b.s1.b1);
			break;
		case 4:
			snprintf(str, STR_SIZE, "%d%d%d%d", b.s2.b4, b.s2.b3, b.s2.b2, b.s2.b1);
			break;
		case 8:
			snprintf(str, STR_SIZE, "%02o", b.num);
			break;
		case 16:
			snprintf(str, STR_SIZE, "%01x%01x", b.s4.b2, b.s4.b1);
			break;
		default:
			snprintf(str, STR_SIZE, "%d", b.num);
	}
	printf("%s\n", removeZero(str));
}

const char *removeZero(const char *str) {
	const char* s;
	int len = strlen(str);
	
	for (s = str; *s == (const char)'0' && *s != (const char)'\0'; s++) {}
	if (*s == '\0') s--;
	return s;
}

int main(void) {
	bit b;
	int i;
	int n[] = {2, 4, 8, 16, 10};
	int len = size(n);
	
	printf("input1(NO_INPUTSTR)\n");
	b.num = getNum(NO_INPUTSTR);
	for (i = 0; i < len; i++) {
		printf("base = %d : ", n[i]);
		print(b, n[i]);
	}
	
	printf("input2(ADD_INPUTSTR)\n");
	b.num = getNum(ADD_INPUTSTR, "input : ");
	for (i = 0; i < len; i++) {
		printf("base = %d : ", n[i]);
		print(b, n[i]);
	}
	
	return 0;
}