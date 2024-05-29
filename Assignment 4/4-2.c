/**
 * 과제 4-(2) 정렬
 * 
 * 사전 파일 재정렬 (삽입/퀵/힙)
*/

#include "sortings.h"

int main(void) {
    record *arrays[3] = { NULL, };
    for (int i = 0; i < 3; i++) {
        arrays[i] = (record *)calloc(WORD_COUNT, sizeof(record));
        load(arrays[i]);                    // 데이터 로드
        sort(arrays[i], (sort_type)i);      // 1차 정렬
    }

    // 2차 정렬
    clock_t is_time = sort(arrays[0], INSERTION_SORT);
    clock_t qs_time = sort(arrays[1], QUICK_SORT);
    clock_t hs_time = sort(arrays[2], HEAP_SORT);

    printf("삽입 정렬: %.3f초\n", (double)is_time / CLOCKS_PER_SEC);
    printf("퀵 정렬: %.3f초\n", (double)qs_time / CLOCKS_PER_SEC);
    printf("힙 정렬: %.3f초\n", (double)hs_time / CLOCKS_PER_SEC);

    for (int i = 0; i < 3; i++) {
        free(arrays[i]);
        arrays[i] = NULL;
    }
    
    return 0;
}