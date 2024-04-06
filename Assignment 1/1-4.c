/**
 * 과제 1-(4) 희소 행렬 저장 방식의 곱셈
 * 
 * 20234748 나선우
 * 
*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_SIZE 30
#define MAX_TERM_LEN 30

struct term {
    int row;
    int col;
    int value;
};

typedef struct {
    struct term *terms;
    int rows;
    int cols;
    int count;
} sparse_matrix;


sparse_matrix sparse_matrix_mult(sparse_matrix a, sparse_matrix b);
void input_matrix(sparse_matrix *matrix);
void print_matrix(sparse_matrix matrix);

int main(void) {
    sparse_matrix matrixA, matrixB;

    input_matrix(&matrixA);
    input_matrix(&matrixB);

    sparse_matrix result = sparse_matrix_mult(matrixA, matrixB);

    printf("Result of (matrix A) × (matrix B)\n");
    print_matrix(result);

    return 0;
}

sparse_matrix sparse_matrix_mult(sparse_matrix a, sparse_matrix b) {
    // 곱할 수 있는 행렬인지 검사
    assert(a.cols == b.rows);

    sparse_matrix result = {
        .terms = (struct term*)calloc(MAX_TERM_LEN, sizeof(struct term)),
        .rows = a.rows,
        .cols = b.cols,
        .count = 0,
    };

    // 희소행렬의 곱셈
    for (int i = 0; i < a.count; i++) {
        for (int j = 0; j < b.count; j++) {
            // 적절한 위치의 수를 찾으면 곱해서 저장한다.
            if (a.terms[i].col == b.terms[j].row) {
                int mul = a.terms[i].value * b.terms[j].value;
                int row = a.terms[i].row;
                int col = b.terms[j].col;
                
                // 해당 위치에 이미 값이 있는지 (=> 0이 아닌지) 점검
                // 있으면 기존 값과 더하고, 없으면 새로 저장한다.
                bool found = false;
                for (int k = 0; k < result.count; k++) {
                    if (result.terms[k].row == row && result.terms[k].col == col) {
                        result.terms[k].value += mul;
                        found = true;
                        break;
                    }
                }
                if (!found) 
                    result.terms[result.count++] = (struct term){ row, col, mul };
            }
        }
    }
    return result;
}

void input_matrix(sparse_matrix *matrix) {
    struct term terms[MAX_TERM_LEN] = { {0, 0, 0}, };
    char buf[MAX_BUF_SIZE], *token = NULL;
    int row = 0, col = 0, value = 0, total_col = 0;
    int real_len = 0;

    // EOF 전까지 매 줄을 읽음
    printf("Input matrix (공백으로 구분, Ctrl+Z로 입력 종료)\n");
    while (!feof(stdin) && fgets(buf, sizeof buf, stdin) != NULL) {
        // 첫 줄이라면 column 수 계산
        if (row == 0) {
            for(int i = 0; buf[i] != '\0'; i++)
                if(buf[i] == ' ')
                    total_col++;
            total_col++;
        }
        
        col = 0;
        for (token = strtok(buf, " "); token; token = strtok(NULL, " ")) {
            value = atoi(token);
            // 0이 아닌 경우에만 항을 저장.
            if (value != 0) {
                terms[real_len] = (struct term){ row, col, value };
                real_len++;
            }
            col++;
        }
        row++;
    }

    // while문을 나왔다는 건 EOF 라는 것. 플래그 클리어
    clearerr(stdin);

    *matrix = (sparse_matrix){ 
        .terms = (struct terms*)calloc(real_len, sizeof(struct term)),
        .rows = row, .cols = col, .count = real_len
    };
    for (int i = 0; i < matrix->count; i++) {
        matrix->terms[i] = terms[i];
    }
}


// 구조체의 크기가 크지 않으므로, 복사 전달
void print_matrix(sparse_matrix matrix) {
    int idx = 0;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            if (j == 0) { 
                if (i == 0)                     printf("┌ ");
                else if (i == matrix.rows - 1)  printf("└ ");
                else                            printf("│ ");
            }

            // matrix.terms에 값이 있을 때는 값을 출력, 없으면 0 출력
            printf("%d ", (idx < matrix.count 
                && matrix.terms[idx].row == i
                && matrix.terms[idx].col == j) ? matrix.terms[idx++].value : 0);

            if (j == matrix.cols - 1) {
                if (i == 0)                     printf("┐\n");
                else if (i == matrix.rows - 1)  printf("┘\n");
                else                            printf("│\n");
            }
        }
    }
}