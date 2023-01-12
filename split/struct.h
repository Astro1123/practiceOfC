#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>

typedef struct cell {
	char* item;
	struct cell *next;
} Cell;

typedef struct list {
	Cell *top;
	
	#define List struct list
	/* リスト削除 */
	void (*destroy)(List*);
	
	/* データ追加 */
	bool (*push)(List*, char*);
	bool (*add)(List*, int, char*);
	bool (*enqueue)(List*, char*);
	
	/* データ変更 */
	bool (*set)(List*, int, char*);
	
	/* データ削除 */
	bool (*delete)(List*, int);
	void (*clear)(List*);
	
	/* データ取得 */
	char* (*get)(List*, int);
	char* (*pop)(List*);
	char* (*dequeue)(List*);
	
	/* 情報取得 */
	bool (*isEmpty)(List*);
	int (*size)(List*);
	
	/* 検索 */
	int (*indexOf)(List*, char*);
	#undef List
} List;

void print_data(char *s);
char* make_null_data(void);
int compare_data(char* s1, char* s2);

#endif /* STRUCT_H */