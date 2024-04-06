/**
 * 과제 1-(1) 자료구조 만들기
 * 
 * 20234748 나선우
 * 
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 10
#define PRINT_TITLE(str) printf("<<<< " str " >>>>\n")

int main(void) {
    int a, b, c;
    
    printf("a, b, c 입력: ");
    scanf("%d%d%d", &a, &b, &c);

/** 데이터 저장 */

    // 메인 포인터. void **를 가리키는 포인터이다.
    void ***ptr = (void ***)calloc(3, sizeof(void **));

    // ptr의 각 요소에는 void *크기로 메모리를 할당한다.
    ptr[0] = (void **)calloc(a, sizeof(void *));
    ptr[1] = (void **)calloc(b, sizeof(void *));
    ptr[2] = (void **)calloc(c, sizeof(void *));

    // ptr[0] : 정수들의 포인터
    for (int i = 0; i < a; i++) {
        // ptr[0][0..a]에 메모리를 할당한 후,
        ptr[0][i] = calloc(b, sizeof(int));
        for (int j = 0; j < b; j++) {
            // 1부터 차례대로 값을 대입한다.
            ((int *)ptr[0][i])[j] = b*i + (j+1);
        }
    }

    // ptr[1] : 실수들의 포인터
    for (int i = 0; i < b; i++) {
        // ptr[1][0..b]에 메모리를 할당한 후,
        ptr[1][i] = calloc(c, sizeof(double));
        for (int j = 0; j < c; j++) {
            // 1.0부터 차례대로 값을 대입한다.
            ((double *)ptr[1][i])[j] = 1 + (b*i + j)*0.1;
        }
    }

    // ptr[2] : 문자열의 포인터
    for (int i = 0; i < c; i++) {
        // ptr[2][i]가 이미 void *므로, char *의 배열로 할당한다.
        ptr[2][i] = (char **)calloc(a, sizeof(char *));
        for (int j = 0; j < a; j++) {
            // 문자열을 저장하기 위한 배열을 한 번 더 할당한다.
            ((char **)ptr[2][i])[j] = (char *)calloc(MAX_STR_LEN + 1, sizeof(char));
            // 해당 주소에 문자열을 저장한다.
            sprintf(((char **)ptr[2][i])[j], "Hi%d", c*i + (j+1));
        }
    }

/** 출력 */

    PRINT_TITLE("ptr");
    // ptr[0..2]의 값 출력
    printf("ptr[0]: %p, ptr[1]: %p, ptr[2]: %p\n\n", (void *)ptr[0], (void *)ptr[1], (void *)ptr[2]);

    PRINT_TITLE("ptr[0]");
    for (int i = 0; i < a; i++) {
        // int 배열의 주소와 저장된 값 출력
        printf("ptr[0][%d]: %p = { ", i, ptr[0][i]);
        for (int j = 0; j < b; j++) {
            printf("%d, ", ((int *)ptr[0][i])[j]);
        }
        printf("\b\b }\n");
    }
    putchar('\n');

    PRINT_TITLE("ptr[1]");
    for (int i = 0; i < b; i++) {
        // double 배열의 주소와 저장된 값 출력
        printf("ptr[1][%d]: %p = { ", i, ptr[1][i]);
        for (int j = 0; j < c; j++) {
            printf("%.1f, ", ((double *)ptr[1][i])[j]);
        }
        printf("\b\b }\n");
    }
    putchar('\n');

    PRINT_TITLE("ptr[2]");
    for (int i = 0; i < c; i++) {
        // char[] 배열의 주소와 저장된 값 출력
        printf("ptr[2][%d]: %p = { ", i, ptr[2][i]);
        for (int j = 0; j < a; j++) {
            printf("\"%s\", ", ((char **)ptr[2][i])[j]);
        }
        printf("\b\b }\n");
    }

/** 메모리 해제 */

    // ptr[0][0..a] 해제
    for (int i = 0; i < a; i++) {
        free(ptr[0][i]);
    }
    // ptr[1][0..b] 해제
    for (int i = 0; i < b; i++) {
        free(ptr[1][i]);
    }
    // ptr[2][0..c][0..a] 해제
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < a; j++) {
            free(((char **)ptr[2][i])[j]);
        }
        free(ptr[2][i]);
    }

    // ptr[0..2] 해제
    for (int i = 0; i < 3; i++) {
        free(ptr[i]);
    }
    
    // ptr 해제
    free(ptr);

    return 0;
}