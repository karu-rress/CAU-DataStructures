/**
 * 과제 6-(1) 해시/탐색트리
 * 
 * 해시
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SLOT_LENGTH 200 // 슬롯의 최대 길이
#define MAX_TABLE_SIZE 7000 // 해시테이블의 크기

typedef struct tagNode {
    char key[MAX_SLOT_LENGTH];
    char value[MAX_SLOT_LENGTH];
    struct tagNode *next;
} node;

int hash(const char *key);
const char* dict_search(const node *restrict head, const char *restrict query, int *cmps);
void insert_node(node *head, const char *restrict key, const char *restrict value);
void load(node **table);
void run(const node **table);
void clean(node **table);

int main(void) {
    node **hash_table = (node **)calloc(MAX_TABLE_SIZE, sizeof(node *));
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        hash_table[i] = (node *)malloc(sizeof(node));
        hash_table[i]->key[0] = '\0';
        hash_table[i]->next = NULL;
    }

    load(hash_table);
    run(hash_table);    
    
    clean(hash_table);

    return 0;
}

int hash(const char *key) {
    int result = 1;
    for (int i = 0; key[i] != '\0'; i++) {
        result = (result * (key[i] << (key[i] % 4))) % MAX_TABLE_SIZE;
    }

    return result;
}

const char* dict_search(const node *restrict head, const char *restrict query, int *cmps) {
    *cmps = 0;
    for (const node *p = head; p != NULL; p = p->next) {
        (*cmps)++;
        if (strcmp(p->key, query) == 0)
            return p->value;
    }
    return NULL;
}

void insert_node(node *head, const char *restrict key, const char *restrict value) {
    node *new = (node *)malloc(sizeof(node));
    strcpy(new->key, key);
    strcpy(new->value, value ? value : "");

    node *p = head;
    while (p->next != NULL && strcmp(p->next->key, new->key) < 0)
        p = p->next;
    
    new->next = p->next;
    p->next = new;
}

void load(node **table) {
    FILE *fp = fopen("randdict_utf8.txt", "r");
    char line[MAX_SLOT_LENGTH * 2] = "";

    while (fgets(line, sizeof line, fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // \n 제거
        char *str1 = strtok(line, " : ");
        char *str2 = strtok(NULL, " : ");
        insert_node(table[hash(str1)], str1, str2); // 해시값을 이용하여 삽입
    }
    fclose(fp);
}

void run(const node **table) {
    char input[MAX_SLOT_LENGTH] = "";
    int hash_result = 0, cmps = 0;
    printf("단어를 입력하세요: ");
    while (scanf("%s", input) != EOF) {
        hash_result = hash(input);
        const char *search_result = dict_search(table[hash_result], input, &cmps);

        if (search_result != NULL) {
            printf("[slot %d] %s (Compared: %d times)\n", hash_result, search_result, cmps);
        }
        else {
            printf("찾는 단어가 없습니다.\n");
        }

        printf("\n단어를 입력하세요: ");
    }
}

void clean(node **table) {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        node *p = table[i], *rem = NULL;
        while (p) {
            rem = p;
            p = p->next;
            free(rem);
        }
    }
    free(table);
}