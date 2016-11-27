
#include <stdbool.h>
#include <stdlib.h>
#define Q_LIST_H
#define qList(Template) list_constructor(sizeof(Template))
#define qListIterator(Template) listIterator_constructor(sizeof(Template))
#define ITERATOR_TYPE_NORMAL 0
#define ITERATOR_TYPE_REVERSE 1
typedef struct List List;
typedef struct ListIterator ListIterator;

typedef double LIST_TYPE;

typedef struct ListNode{
    void* ptr;
    int step;
    struct ListNode* prev;
    struct ListNode* next;
}ListNode;

struct List{
    ListNode* first;
    ListNode* last;
    int step;
    int size;
};

struct ListIterator{
    ListNode* curr;
    int step;
    int FLAG_TYPE;
};



// functions 
// note the absence of reference
List* list_constructor(int stepLength);
ListNode* listNode_constructor(int stepLength);
ListIterator* listIterator_constructor(int stepLength);

void* list_ptr_at(List* lis);
bool list_empty(List* lis);
int list_size(List* lis);

void list_clear(List* lis);

//      a, b, c, ...,m, where, n, ...
// =>   a, b, c, ...,m, value, where, n, ...
void list_insert(List* lis, ListIterator* where, void* value);
void list_erase(List* lst,ListIterator* where);

void list_push_back(List* lis, void* value);
void list_pop_back(List* lis);
void list_push_front(List* lis, void* value);
void list_pop_front(List* lis);


ListIterator list_begin(List* lis);
ListIterator list_end(List* lis);
void ListIterator_self_increase(ListIterator* pIter);
void ListIterator_self_decrease(ListIterator* pIter);

bool ListIterator_equal(ListIterator iter_a, ListIterator iter_b);
bool ListIterator_not_equal(ListIterator iter_a, ListIterator iter_b);

// you have to write like:
// ---------------------------------------
// LIST_TYPE value;
// *list_get_data_ptr(some_iter) = value;
// ---------------------------------------
void* list_get_data_ptr(ListIterator* iter);
