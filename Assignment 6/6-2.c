/**
 * 과제 6-(2) 해시/탐색트리
 * 
 * AVL 트리 만들기
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100

typedef struct tagNode {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
    struct tagNode *left;
    struct tagNode *right;
    int height;
} node;

void make_tree(node **proot);
int count_nodes(const node *root);
const node *search(const node *restrict root, const char *restrict key);

int node_height(const node *root);
int max(int a, int b);
void update_height(node *root);
int get_balance(const node *root);

node *right_rotate(node *y);
node *left_rotate(node *x);
node *insert(node *n, const char *restrict key, const char *restrict value);

int main(void) {
    // 파일 읽기 및 트리 생성
    node *root = NULL;
    make_tree(&root);
    
    int height = node_height(root);
    int count = count_nodes(root);
    printf("트리의 전체 높이는 %d입니다. 트리의 노드 수는 %d개 입니다.\n\n", height, count);

    char input[MAX_LENGTH] = "";
    while (1) {
        printf("단어를 입력하세요: ");
        scanf("%s", input);

        if (strcmp(input, "_EXIT_") == 0)
            return 0;

        const node *result = search(root, input);

        if (result == NULL) // 검색 결과가 없는가?
            printf("단어를 찾을 수 없습니다.\n");
        else
            printf("%s\t(레벨: %d)\n", result->value, node_height(root) - node_height(result));
    }

    return 0;
}

void make_tree(node **proot) {
    FILE *fp = fopen("randdict_utf8.txt", "r");
    char line[MAX_LENGTH * 2] = "";
    int cnt = 0;

    // EOF 전까지 읽음
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0'; // '\n' 제거
        char *str1 = strtok(line, " : ");
        char *str2 = strtok(NULL, " : ");

        *proot = insert(*proot, str1, str2 ? str2 : "");
        cnt++;
    }
    fclose(fp);
    printf("사전 파일을 모두 읽었습니다. %d개의 단어가 있습니다.\n", cnt);
}

int count_nodes(const node *root) {
    if (root == NULL)
        return 0;

    // 서브트리의 크기 계산 (재귀)
    int left = count_nodes(root->left);
    int right = count_nodes(root->right);

    // 각 서브트리의 크기에 현재 노드를 더하여 반환
    return left + right + 1;
}

const node *search(const node *restrict root, const char *restrict key) {
    if (root == NULL) // 노드가 없으면 NULL 반환
        return NULL;

    int cmp = strcmp(root->key, key);
    if (cmp == 0) // 찾던 키라면 현재 노드를 반환
        return root;

    if (cmp > 0) // 키가 더 작으면 왼쪽으로
        return search(root->left, key);

    else // 나머지(키가 크면)인 경우 오른쪽으로 이동
        return search(root->right, key);
}

int node_height(const node *root) {
    return root ? root->height : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void update_height(node *root) {
    if (root == NULL)
        return;
    
    root->height = max(node_height(root->left), node_height(root->right)) + 1;
}

int get_balance(const node *root) {
    return root ? node_height(root->left) - node_height(root->right) : 0;
}

node *right_rotate(node *y) {
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    // 새로운 루트 반환
    return x;
}

node *left_rotate(node *x) {
    node *y = x->right;
    node *T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    // 새로운 루트 반환
    return y;
}

node *insert(node *n, const char *restrict key, const char *restrict value) {
    if (n == NULL) {
        node *new = (node *)malloc(sizeof(node));
        strcpy(new->key, key);
        strcpy(new->value, value);
        new->left = new->right = NULL;
        new->height = 1; // 새로운 노드의 높이는 1
        return new;
    }

    if (strcmp(key, n->key) < 0)        // 키가 작으면 왼쪽으로
        n->left = insert(n->left, key, value);
    else if (strcmp(key, n->key) > 0)   // 키가 크면 오른쪽으로
        n->right = insert(n->right, key, value);
    else                                // 키가 같으면 변경 없음
        return n;

    // 높이 갱신
    update_height(n);

    // 균형 조정
    int balance = get_balance(n);

    // LL
    if (balance > 1 && strcmp(key, n->left->key) < 0)
        return right_rotate(n);

    // RR
    if (balance < -1 && strcmp(key, n->right->key) > 0)
        return left_rotate(n);
    
    // LR
    if (balance > 1 && strcmp(key, n->left->key) > 0) {
        n->left = left_rotate(n->left);
        return right_rotate(n);
    }

    // RL
    if (balance < -1 && strcmp(key, n->right->key) < 0) {
        n->right = right_rotate(n->right);
        return left_rotate(n);
    }

    return n;
}