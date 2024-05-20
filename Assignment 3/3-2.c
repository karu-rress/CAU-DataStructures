/**
 * 과제 3-(2) 연결 리스트
 * 
 * 정렬의 성능 평가
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 200
#define VECT_LENGTH 48406

typedef struct tagNode {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
    struct tagNode *next;
} node;

const char* dict_search(const node *restrict head, const char *restrict query);
void insert_node(node **phead, const char *restrict key, const char *restrict value);
void load(node **phead);
void load_vector(node **phead);
void run(const node *head);
void clean(node *head);
void clean_vector(node *head);

int main(void) {
    node *head = NULL;

    clock_t start = clock();
    load(&head);
    clock_t list_time = clock() - start;
    clean(head);

    start = clock();
    load_vector(&head);
    clock_t vector_time = clock() - start;
    clean_vector(head);

    printf("연결리스트에 담으며 정렬: %.3f초 소요\n", (double)list_time / CLOCKS_PER_SEC);
    printf("배열에 담은 후 정렬: %.3f초 소요\n", (double)vector_time / CLOCKS_PER_SEC);

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


void load_vector(node **phead) {
    FILE *fp = fopen("randdict_utf8.txt", "r");
    node *vector = (node *)calloc(VECT_LENGTH, sizeof(node));
    char line[MAX_LENGTH * 2] = "";

    while (fgets(line, sizeof line, fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // \n 제거
        char *str1 = strtok(line, " : ");
        char *str2 = strtok(NULL, "\n");

        for (int i = 0; i < VECT_LENGTH; i++) {
            strcpy(vector[i].key, str1);
            strcpy(vector[i].value, str2);
            // 사실상 필요하지 않으나, 일관성을 위해 할당
            vector[i].next = (i == VECT_LENGTH - 1) ? NULL : &vector[i + 1];
        }
    }

    // selection sort
    node tmp;
    for (int i = 0; i < VECT_LENGTH - 1; i++) {
        for (int j = i; j < VECT_LENGTH; j++) {
            if (strcmp(vector[i].key, vector[j].key) < 0) {
                tmp = vector[i];
                vector[i] = vector[j];
                vector[j] = tmp;
            }
        }
    }

    *phead = vector;
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

void clean_vector(node *head) {
    free(head); // 연속된 메모리이므로 free()로 한번에 해제
}