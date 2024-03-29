#include "list_itr.h"
#include "listInternal.h"
#include <stdlib.h> /*< free >*/

ListItr ListItr_Begin(const List* _list) {
    return (NULL == _list) ? NULL : (_list->m_head).m_next;
}

ListItr ListItr_End(const List* _list) {
    return (NULL == _list) ? NULL : (_list->m_tail).m_next;
}

int ListItr_Equals(const ListItr _a, const ListItr _b) { return (_a == _b); }

ListItr ListItr_Next(ListItr _itr) {
    Node* node = _itr;
    Node* nexNode;
    if (NULL == _itr) {
        return NULL;
    }
    nexNode = node->m_next;
    return nexNode;
}

ListItr ListItr_Prev(ListItr _itr) {
    Node* node = _itr;
    Node* prevNode;

    if (NULL == _itr) {
        return NULL;
    }

    prevNode = node->m_prev;
    if (node->m_prev == prevNode->m_prev) {
        return node;
    }
    return node->m_prev;
}

void* ListItr_Get(ListItr _itr) {
    Node* node = _itr;
    return (NULL == _itr) ? NULL : node->m_item;
}

void* ListItr_Set(ListItr _itr, void* _element) {
    Node* node = _itr;
    void* item;
    if (NULL == _itr || NULL == _element) {
        return NULL;
    }
    item = node->m_item;
    node->m_item = _element;
    return item;
}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element) {
    Node* node = _itr;
    Node* newNode;
    if (NULL == _itr || NULL == _element) {
        return NULL;
    }

    newNode = NodeCreate(_element);
    if (newNode == NULL) {
        return NULL;
    }

    PushNode(node->m_prev, newNode);
    return newNode;
}

void* ListItr_Remove(ListItr _itr) {
    Node* node = _itr;
    void* item;
    if (NULL == _itr) {
        return NULL;
    }

    PopNode(node->m_prev, node->m_next);
    item = node->m_item;
    free(node);
    return item;
}