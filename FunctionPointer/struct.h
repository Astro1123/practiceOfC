#ifndef STRUCT_H
#define STRUCT_H

typedef struct {
	const char* name;
	int (*func)(int*, int);
} sortMethod;

typedef struct cell {
	sortMethod item;
	struct cell *next;
} Cell;

typedef struct list {
	Cell *top;
	
	#define List struct list
	/* リスト削除 */
	void (*destroy)(List*);
	
	/* データ追加 */
	bool (*push)(List*, sortMethod);
	bool (*add)(List*, int, sortMethod);
	bool (*enqueue)(List*, sortMethod);
	
	/* データ変更 */
	bool (*set)(List*, int, sortMethod);
	
	/* データ削除 */
	bool (*delete)(List*, int);
	void (*clear)(List*);
	
	/* データ取得 */
	sortMethod (*get)(List*, int);
	sortMethod (*pop)(List*);
	sortMethod (*dequeue)(List*);
	
	/* 情報取得 */
	bool (*isEmpty)(List*);
	int (*size)(List*);
	
	/* 検索 */
	int (*indexOf)(List*, sortMethod);
	#undef List
} List;

#endif /* STRUCT_H */