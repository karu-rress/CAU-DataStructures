#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

void insert_node(DlistNode *before, DlistNode *new_node) {
    new_node->llink = before;               // 새 노드의 이전 노드는 before
    new_node->rlink = before->rlink;        // 새 노드의 다음 노드는 before의 다음
    before->rlink->llink = new_node;        // before의 다음 노드의 이전 노드는 새 노드
    before->rlink = new_node;               // before의 다음 노드는 새 노드
}

// removed는 없어도 되지만(p + 1), p가 없으면 O(n)으로 찾아야 함.
void remove_node(DlistNode **phead_node, DlistNode *removed) {
    if (removed == *phead_node) // 헤드(더미)만 있다면 동작 안 함
        return;

    removed->llink->rlink = removed->rlink; // 위치 맞춰주고 
    removed->rlink->llink = removed->llink;

    free(removed);                          // 삭제
}

void display(DlistNode *head) {
    DlistNode *p = head->rlink;
    if (p == NULL) {
        printf("List is empty.\n");
        return;
    }
    while (p != head) {
        printf("%d->", p->data);
        p = p->rlink;
    }
    printf("\n");
}

DlistNode *search(DlistNode *head, element x) {
    DlistNode *p;
    for (p = head->rlink; p != NULL; p = p->rlink) {
        if (p->data == x)
            return p;
    }
    return NULL; // same as return p
}

int main() {
    DlistNode *head = (DlistNode*)malloc(sizeof(DlistNode));
    head->rlink = head;
    head->llink = head;
    DlistNode *p = NULL;
    DlistNode *cur = NULL;

    p = (DlistNode*)malloc(sizeof(DlistNode));
    p->data = 10;
    insert_node(head, p);
    cur = p;

    p = (DlistNode*)malloc(sizeof(DlistNode));
    p->data = 20;
    insert_node(cur, p);
    cur = p;

    p = (DlistNode*)malloc(sizeof(DlistNode));
    p->data = 30;
    insert_node(cur, p);
    cur = p;

    display(head);

    return 0;
}
