#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct cell {
	Data item;
	struct cell *next;
} Cell;

typedef struct list {
	Cell *top;
	
	#define List struct list
	/* リスト削除 */
	void (*destroy)(List*);
	
	/* データ追加 */
	bool (*push)(List*, Data);
	bool (*add)(List*, int, Data);
	bool (*enqueue)(List*, Data);
	
	/* データ変更 */
	bool (*set)(List*, int, Data);
	
	/* データ削除 */
	bool (*delete)(List*, int);
	void (*clear)(List*);
	
	/* データ取得 */
	Data (*get)(List*, int);
	Data (*pop)(List*);
	Data (*dequeue)(List*);
	
	/* 情報取得 */
	bool (*isEmpty)(List*);
	int (*size)(List*);
	
	/* 検索 */
	int (*indexOf)(List*, Data);
	#undef List
} List;

List *make_list(void);
void print_list(List *list);

#endif /* LINKEDLIST_H */