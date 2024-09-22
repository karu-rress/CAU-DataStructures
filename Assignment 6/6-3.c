/**
 * 과제 6-(3) 해시/탐색트리
 * 
 * B-트리 만들기
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100
#define MAX_KEYS 4
#define MIN_KEYS (MAX_KEYS / 2)
#define MAX_CHILDREN (MAX_KEYS + 1)

// Convert normal tree to B-tree

typedef struct tagNode {
    int key_count;
    char key[MAX_KEYS][MAX_LENGTH];
    char value[MAX_KEYS][MAX_LENGTH];
    struct tagNode *children[MAX_CHILDREN];
    bool leaf;
} node;

void make_tree(node **proot);
int get_height(const node *root);
int count_nodes(const node *root);
const node *search(const node *restrict root, const char *restrict key);

int main(void) {
    // 파일 읽기 및 트리 생성
    node *root = NULL;
    make_tree(&root);
    
    int height = get_height(root);
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
            printf("%s\t(레벨: %d)\n", result->value, get_height(root) - get_height(result));
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

        // 루트가 없다면 루트에 삽입
        if (*proot == NULL) {
            node *new_node = (node *)malloc(sizeof(node));
            memset(new_node, 0, sizeof(node));

            new_node->key_count = 1;
            strcpy(new_node->key[0], str1);
            strcpy(new_node->value[0], str2 ? str2 : "");
            new_node->leaf = true;

            *proot = new_node;
            cnt++;
            continue;
        }

        // 노드를 따라가며 삽입
        



        node *current = *proot; // 루트부터 시작하여
        while (1) {
            if (strcmp(new_node->key, current->key) < 0) { // 앞선 단어면 왼쪽으로
                if (current->left == NULL) { // 탐색이 실패한 곳이 저장 위치
                    current->left = new_node;
                    break;
                }
                else // 왼쪽으로 한 칸 전진
                    current = current->left;
            }
            else { // 뒤의 단어면 오른쪽으로
                if (current->right == NULL) { 
                    current->right = new_node;
                    break;
                }
                else // 오른쪽으로 한 칸 전진
                    current = current->right;
            }
        }
    }
    fclose(fp);
    printf("사전 파일을 모두 읽었습니다. %d개의 단어가 있습니다.\n", cnt);
}

int get_height(const node *root) {
    if (root == NULL)
        return 0;

    // 서브트리의 크기 계산 (재귀)
    int left = get_height(root->left);
    int right = get_height(root->right);

    // 더 큰 서브리트의 높이에 현재 노드를 더하여 반환
    return (left > right) ? left + 1 : right + 1;
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