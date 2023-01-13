#ifndef VOID_LINKED_LIST_H
#define VOID_LINKED_LIST_H

#include <stdbool.h>
#include "ListDefine.h"
#define Data void*

typedef struct void_cell {
	Data item;
	struct void_cell *next;
} VoidCell;

typedef struct void_list {
	VoidCell *top;
	
	#define List struct void_list
	
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
	
	/* 表示、比較 */
	void (*printList)(List*);
	int (*compare)(Data, Data);
	
	/* 設定 */
	void (*setPrint)(List*, void (*)(List*));
	void (*setCompare)(List*, int (*)(Data, Data));
	#undef List
} VoidList;

#undef Data

VoidList* make_void_list(void);

#endif /* VOID_LINKED_LIST_H */