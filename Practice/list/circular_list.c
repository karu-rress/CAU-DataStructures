#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {
    element data;
    struct DlistNode *link;
} DlistNode;

void insert_first(DlistNode **phead, DlistNode *node) {
    if (*phead == NULL) { // 리스트가 비어있음
        *phead = node; // 현재 노드가 head
        node->link = node; // 순환 형태로 구성
    }
    else {
        node->link = (*phead)->link; // 첫 노드를 new_node의 다음으로
        (*phead)->link = node; // head 위치에 있던 게 새 노드를 가리킴
    }
}

void insert_last(DlistNode **phead, DlistNode *node) {
    if (*phead == NULL) {
        *phead = node;
        node->link = node;
    }
    else {
        node->link = (*phead)->link;
        (*phead)->link = node;
        *phead = node; // head 자체가 바뀜 
    }
}

// removed는 없어도 되지만(p + 1), p가 없으면 O(n)으로 찾아야 함.
void remove_node(DlistNode **phead, DlistNode *p, DlistNode *removed) {
    if (removed == *phead) { // same as p == NULL
        *phead = removed->link; // 헤드값 저장 : same as *phead = (*phead)->link;
    }
    else {
        p->link = removed->link;
    }
    free(removed);
}

void display(DlistNode *head) {
    DlistNode *p = head;
    while (p != head->link) {
        printf("%d->", p->data);
        p = p->link;
    }
    printf("\n");
}

DlistNode *search(DlistNode *head, element x) {
    DlistNode *p;
    for (p = head; p != head->link; p = p->link) {
        if (p->data == x)
            return p;
    }
    return NULL; // same as return p
}

DlistNode *concat_simple(DlistNode *head1, DlistNode *head2) {
    DlistNode *p;
    
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    for (p = head1; p->link != NULL; p = p->link) { }

    // 현재 p->link는 NULL
    p->link = head2;
    return head1;
}

DlistNode *concat_each(DlistNode *head1, DlistNode *head2) {
    DlistNode *p1 = head1, *p2 = head2;
    DlistNode *result = NULL, *c = NULL;

    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    c = result = head1;
    p1 = p1->link;

    while (1) {
        if (p2 != NULL) {
            c->link = p2;
            p2 = p2->link;
            c = c->link;
        }

        if (p1 != NULL) {
            c->link = p1;
            p1 = p1->link;
            c = c->link;
        }

        printf("p1 = %p, p2 = %p\n", (void *)p1, (void *)p2);
        if (p1 == NULL && p2 == NULL)
            break;
    }

    return result;
}

DlistNode *reverse(DlistNode *head) {
    DlistNode *p, *q, *r;
    p = head; // 역순으로 만들 원본 리스트
    q = NULL; // 역순으로 만들 노드
    
    while (p != NULL) {
        r = q; // q 쫓아가는 놈 (q-1)
        q = p;
        p = p->link; // p는 앞으로 가고
        q->link = r; // q가 노드 순서를 바꿔버림
    }

    return q;
}

int main() {
    DlistNode *head = NULL;
    DlistNode *p = NULL;

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 10;
    insert_node(&head, p);

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 20;
    insert_node(&head, p);

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 30;
    insert_node(&head, p);

    display(head);


    

    return 0;
}
