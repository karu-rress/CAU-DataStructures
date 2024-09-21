#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {
    element data;
    struct DlistNode *link;
} DlistNode;

void insert_node(DlistNode **phead, DlistNode *p, DlistNode *new_node) {
    if (*phead == NULL) {
        new_node->link = NULL;
        *phead = new_node;
    }
    else if (p == NULL) {
        new_node->link = *phead;
        *phead = new_node;
    }
    else {
        new_node->link = p->link;
        p->link = new_node;
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
    while (p != NULL) {
        printf("%d->", p->data);
        p = p->link;
    }
    printf("\n");
}

DlistNode *search(DlistNode *head, element x) {
    DlistNode *p;
    for (p = head; p != NULL; p = p->link) {
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
    DlistNode *cur = NULL;

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 10;
    insert_node(&head, cur, p);
    cur = p;

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 20;
    insert_node(&head, cur, p);
    cur = p;

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 30;
    insert_node(&head, cur, p);

    DlistNode *head2 = NULL;

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 100;
    insert_node(&head2, NULL, p);
    cur = p;

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 200;
    insert_node(&head2, cur, p);
    cur = p;

    p = (DlistNode *)malloc(sizeof(DlistNode));
    p->data = 300;
    insert_node(&head2, cur, p);
    cur = p;

    display(head);
    display(head2);

    display(reverse(head));

    return 0;
}
