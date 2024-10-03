/**
 * 과제 6-(3) 해시/탐색트리
 *
 * B-트리 만들기
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define T 3

// Convert normal tree to B-tree

typedef struct tagNode {
    int n;
    char key[100][MAX_LENGTH];
    char value[100][MAX_LENGTH];
    struct tagNode* children[100];
    bool leaf;
} node;

node* create_node(void);
void split_child(node* x, int index);
void insert(node** proot, const char* key, const char* value);
void insert_key(node* x, const char* key, const char* value);
void search(const node* root, const char* key, const node** result, int* index);

void make_tree(node** proot);
int get_height(const node* root);
int count_nodes(const node* root);

int main(void)
{
    // 파일 읽기 및 트리 생성
    node* root = NULL;
    make_tree(&root);

    int height = get_height(root);
    int count  = count_nodes(root);
    printf("트리의 전체 높이는 %d입니다. 트리의 노드 수는 %d개 입니다.\n\n", height, count);

    char input[MAX_LENGTH] = "";
    while (1) {
        printf("단어를 입력하세요: ");
        scanf("%s", input);

        if (strcmp(input, "_EXIT_") == 0)
            return 0;

        const node* result;
        int index;
        search(root, input, &result, &index);

        if (result == NULL) // 검색 결과가 없는가?
            printf("단어를 찾을 수 없습니다.\n");
        else
            printf("%s\t(레벨: %d)\n", result->value, get_height(root) - get_height(result));
    }

    return 0;
}

node* create_node(void)
{
    node* new_node = (node*)malloc(sizeof(node));
    memset(new_node, 0, sizeof(node));

    return new_node;
}

void split_child(node* x, int index)
{
    node* z = create_node();
    node* y = x->children[index];

    z->leaf = y->leaf;
    z->n    = T - 1;

    for (int j = 0; j < T - 1; j++) {
        strcpy(z->key[j], y->key[j + T]);
        strcpy(z->value[j], y->value[j + T]);
    }

    if (!y->leaf) {
        for (int j = 0; j < T; j++) {
            z->children[j] = y->children[j + T];
        }
    }

    y->n = T - 1;

    for (int j = x->n + 1; j >= index + 1; j--) {
        x->children[j] = x->children[j - 1];
    }

    x->children[index + 1] = z;

    for (int j = x->n; j > index; j--) {
        strcpy(x->key[j], x->key[j - 1]);
        strcpy(x->value[j], x->value[j - 1]);
    }

    strcpy(x->key[index], y->key[T]);
    strcpy(x->value[index], y->value[T]);
    x->n++;
}

void insert(node** proot, const char* key, const char* value)
{
    if (*proot == NULL) {
        node* new_node = create_node();

        new_node->n = 1;
        strcpy(new_node->key[0], key);
        strcpy(new_node->value[0], value);
        new_node->leaf = true;

        *proot = new_node;
    } else {
        node* root = *proot;

        if (root->n == 2 * T - 1) {
            node* new_node = create_node();

            *proot                = new_node;
            new_node->leaf        = false;
            new_node->n           = 0;
            new_node->children[0] = root;

            split_child(new_node, 0);
            insert_key(new_node, key, value);

        } else {
            insert_key(root, key, value);
        }
    }
}

void insert_key(node* x, const char* key, const char* value)
{
    int i = x->n - 1;

    if (x->leaf) {
        for (; i >= 0 && strcmp(key, x->key[i]) < 0; i--) {
            strcpy(x->key[i + 1], x->key[i]);
            strcpy(x->value[i + 1], x->value[i]);
        }

        strcpy(x->key[i + 1], key);
        strcpy(x->value[i + 1], value);
        x->n++;
    } else {
        while (i >= 0 && strcmp(key, x->key[i]) < 0) {
            i--;
        }

        i++;
        if (x->children[i]->n == 2 * T - 1) {
            split_child(x, i);

            if (strcmp(key, x->key[i]) > 0)
                i++;
        }

        insert_key(x->children[i], key, value);
    }
}

void search(const node* root, const char* key, const node** result, int* index)
{
    *result = NULL;
    *index  = -1;

    if (root == NULL)
        return;

    int i = 0;
    while (i < root->n && strcmp(key, root->key[i]) > 0) {
        i++;
    }

    if (i < root->n && strcmp(key, root->key[i]) == 0) {
        *result = root;
        *index  = i;
        return;
    }

    if (root->leaf) {
        return;
    }

    search(root->children[i], key, result, index);
}

void make_tree(node** proot)
{
    FILE* fp                  = fopen("randdict_utf8.TXT", "r");
    char line[MAX_LENGTH * 2] = "";
    int cnt                   = 0;

    // EOF 전까지 읽음
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0'; // '\n' 제거
        char* str1                = strtok(line, " : ");
        char* str2                = strtok(NULL, " : ");

        insert(proot, str1, str2);
    }
    fclose(fp);
    printf("사전 파일을 모두 읽었습니다. %d개의 단어가 있습니다.\n", cnt);
}

int get_height(const node* root)
{
    if (root == NULL)
        return 0;

    // 어차피 모든 서브트리의 높이는 같으므로 왼쪽 서브트리만 계산
    return get_height(root->children[0]) + 1;
}

int count_nodes(const node* root)
{
    if (root != NULL) {
        // 재귀적으로 모든 서브트리의 크기를 계산
        int count = 1;
        for (int i = 0; i < root->n; i++) {
            count += count_nodes(root->children[i]);
        }
        return count;
    }
    return 0;
}