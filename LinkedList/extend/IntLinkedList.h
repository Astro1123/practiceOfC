#ifndef INT_LINKED_LIST_H
#define INT_LINKED_LIST_H

#include <stdbool.h>
#include "ListDefine.h"
#define Data int

typedef struct int_cell {
	Data item;
	struct int_cell *next;
} IntCell;

typedef struct int_list {
	IntCell *top;
	
	#define List struct int_list
	
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
} IntList;

#undef Data

IntList* make_int_list(void);

#endif /* INT_LINKED_LIST_H */