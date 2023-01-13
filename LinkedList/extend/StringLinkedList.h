#ifndef STRING_LINKED_LIST_H
#define STRING_LINKED_LIST_H

#include <stdbool.h>
#include "ListDefine.h"
#define Data char*

typedef struct str_cell {
	Data item;
	struct str_cell *next;
} StrCell;

typedef struct str_list {
	StrCell *top;
	
	#define List struct str_list
	
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
} StrList;

#undef Data

StrList* make_str_list(void);

#endif /* STRING_LINKED_LIST_H */