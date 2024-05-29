/**
 * 과제 4-(3) 정렬
 * 
 * 내장된 정렬 방법과 비교하기
*/

#include "sortings.h"

int compare(const void *a, const void *b) {
    return strcmp(((record *)a)->key, ((record *)b)->key);
}

int main(void) {
    // C에서는 quick sort를 기본으로 제공한다.
    // qsort()와 내가 만든 quick_sort를 비교한다.
    record *array1 = (record *)calloc(WORD_COUNT, sizeof(record));
    record *array2 = (record *)calloc(WORD_COUNT, sizeof(record));

    load(array1);
    load(array2);

    // 1. 내장 qsort() 사용
    clock_t start = clock();
    qsort(array1, WORD_COUNT, sizeof(record), compare);
    clock_t builtin = clock() - start;
    check_sorted(array1);

    // 2. 새로 만든 quick_sort() 사용
    start = clock();
    quick_sort(array2);
    clock_t my = clock() - start;
    check_sorted(array2);

    printf("C에서 내장된 정렬 방법(qsort): %.3f초\n", (double)builtin / CLOCKS_PER_SEC);
    printf("새로 만든 정렬 방법: %.3f초\n", (double)my / CLOCKS_PER_SEC);

    free(array1);
    free(array2);
    
    return 0;
}