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
	void (*destroy)();
	
	/* データ追加 */
	bool (*push)();
	bool (*add)();
	bool (*enqueue)();
	
	/* データ変更 */
	bool (*set)();
	
	/* データ削除 */
	bool (*delete)();
	void (*clear)();
	
	/* データ取得 */
	Data (*get)();
	Data (*pop)();
	Data (*dequeue)();
	
	/* 情報取得 */
	bool (*isEmpty)();
	int (*size)();
	
	/* 検索 */
	int (*indexOf)();
	#undef List
} List;

List *make_list(void);
void print_list(List *list);

#endif /* LINKEDLIST_H */