#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isSign(char c);
bool isNum(char c);
int _atoi(const char* str);
void print(char *str);

bool isSign(char c) {
	return (c == '+' || c == '-');
}

bool isNum(char c) {
	return (c >= '0' && c <= '9');
}

int _atoi(const char* str) {
	const char *c;
	int res = 0;
	int sign = 1;
	
	if (!str) return 0;
	c = str;
	if (isSign(*c)) {
		if (*c == '-') {
			sign = -1;
		}
		c++;
	}
	for (; isNum(*c); c++) {
		res = res * 10 + (*c - '0');
	}
	return res * sign;
}

int _strlen(const char* str) {
	const char *c;
	if (!str) return -1;
	for (c = str; *c != '\0'; c++);
	return (int)(c - str);
}

void print(char *str) {
	char *s;
	printf("%d\n", _atoi(str));
	printf("##%s\n", s);
}

int main(void) {
	print("7");
	print("-5");
	print("+3");
	print("100a");
	print("a5");
	print("0");
	return 0;
}