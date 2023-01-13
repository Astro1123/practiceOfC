#ifndef BOOL_LINKED_LIST_H
#define BOOL_LINKED_LIST_H

#include <stdbool.h>
#include "ListDefine.h"
#define Data bool

typedef struct bool_cell {
	Data item;
	struct bool_cell *next;
} BoolCell;

typedef struct bool_list {
	BoolCell *top;
	
	#define List struct bool_list
	
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
} BoolList;

#undef Data

BoolList* make_bool_list(void);

#endif /* BOOL_LINKED_LIST_H */