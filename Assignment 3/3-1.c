/**
 * 과제 3-(1) 연결 리스트
 * 
 * 사전 만들기
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 200

// 단일리스트인 이유: 삽입 시 순차탐색 필요,
// 공간복잡도를 복합적으로 고려하여 단일리스트로 구현
typedef struct tagNode {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
    struct tagNode *next;
} node;

const char* dict_search(const node *restrict head, const char *restrict query);
void insert_node(node **phead, const char *restrict key, const char *restrict value);
void load(node **phead);
void run(const node *head);
void clean(node *head);

int main(void) {
    node *head = NULL;

    load(&head);
    run(head);
    clean(head);

    return 0;
}

const char* dict_search(const node *restrict head, const char *restrict query) {
    for (const node *p = head; p != NULL; p = p->next) {
        if (strcmp(p->key, query) == 0)
            return p->value;
    }
    return NULL;
}

void insert_node(node **phead, const char *restrict key, const char *restrict value) {
    node *new = (node *)malloc(sizeof(node));
    strcpy(new->key, key);
    strcpy(new->value, value ? value : "");

    // head가 없거나, 단어가 맨 앞에 오는가?
    if (*phead == NULL || strcmp(new->key, (*phead)->key) < 0) {
        new->next = *phead;
        *phead = new;
    }
    else { // 알파벳 순에 맞추어 삽입할 위치 조정
        node *p = *phead;
        while (p->next != NULL && strcmp(p->next->key, new->key) < 0)
            p = p->next;
        
        new->next = p->next;
        p->next = new;
    }
}

void load(node **phead) {
    FILE *fp = fopen("randdict_utf8.txt", "r");
    char line[MAX_LENGTH * 2] = "";

    while (fgets(line, sizeof line, fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // \n 제거
        char *str1 = strtok(line, " : ");
        char *str2 = strtok(NULL, " : ");
        insert_node(phead, str1, str2);
    }
    fclose(fp);
}

void run(const node *head) {
    char input[MAX_LENGTH] = "";
    const char *result = NULL;

    printf(">> ");
    while (scanf("%s", input) != EOF) {
        if ((result = dict_search(head, input)) != NULL)
            puts(result);
        else
            puts("찾는 단어가 없습니다.");
        printf(">> ");
    }
}

void clean(node *head) {
    node *p = head, *rem = NULL;
    while (p) {
        rem = p;
        p = p->next;
        free(rem);
    }
}