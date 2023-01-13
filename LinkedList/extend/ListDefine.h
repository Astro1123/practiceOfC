#ifndef LINKED_LIST_DEFINE_H
#define LINKED_LIST_DEFINE_H

#define ListDestroy(list) list->destroy(list)

#define ListPush(list, x) list->push(list, x)
#define ListAdd(list, n, x) list->add(list, n, x)
#define ListEnqueue(list, x) list->enqueue(list, x)

#define ListSet(list, n, x) list->set(list, n, x)

#define ListDelete(list, n) list->delete(list, n)
#define ListClear(list) list->clear(list)

#define ListGet(list, n) list->get(list, n)
#define ListPop(list) list->push(list)
#define ListDequeue(list) list->dequeue(list)

#define ListEmpty(list) list->isEmpty(list)
#define ListSize(list) list->size(list)
#define ListIndexOf(list, x) list->indexOf(list, x)

#define ListPrint(list) list->printList(list)
#define CompareData(list, a, b) list->compare(a, b)
#define SetListPrint(list, func) list->setPrint(list, func)
#define SetCompareData(list, func) list->setCompare(list, func)

#define MakeDoubleList make_double_list
#define MakeIntList make_int_list
#define MakeStrList make_str_list
#define MakeBoolList make_bool_list
#define MakeCharList make_char_list
#define MakeVoidList make_void_list

#endif /* LINKED_LIST_DEFINE_H */