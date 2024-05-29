/**
 * sortings.c
 * 
 * 다음 과제에서 공통적으로 사용하는
 * 정렬 함수들을 정의합니다.
 * 
 * 4-(1) 사전 파일 정렬하기
 * 4-(2) 사전 파일 재정렬하기
 * 4-(3) 내장된 정렬 방법과 비교하기
*/

#include "sortings.h"

// 정렬 및 검증 후, 정렬 시간 반환
clock_t sort(record *array, sort_type type) {
    clock_t start, end;

    switch (type) {
        case INSERTION_SORT:
            start = clock();
            insertion_sort(array);
            end = clock();
            break;
        case QUICK_SORT:
            start = clock();
            quick_sort(array);
            end = clock();
            break;
        case HEAP_SORT:
            start = clock();
            heap_sort(array);
            end = clock();
            break;
    }

    // 정렬 검증. assert 및 기타 오류로 멈춘다면, 잘못된 것.
    check_sorted(array);

    switch (type)
    {
    case INSERTION_SORT:
        puts("삽입 정렬 완료");
        break;
    case QUICK_SORT:
        puts("퀵 정렬 완료");
        break;
    case HEAP_SORT:
        puts("힙 정렬 완료");
        break;
    }

    return end - start;
}

void check_sorted(record *array) {
    for (int i = 0; i < WORD_COUNT - 1; i++) {
        int result = strcmp(array[i].key, array[i + 1].key);
        assert(result <= 0);
    }
}

void load(record *array) {
    FILE *fp = fopen("randdict_utf8.txt", "r");
    char line[MAX_LENGTH * 2] = "";

    for (int i = 0; i < WORD_COUNT; i++) {
        fgets(line, sizeof(line), fp);
        line[strcspn(line, "\n")] = '\0'; // '\n' 제거

        char *str1 = strtok(line, " : ");
        char *str2 = strtok(NULL, " : ");

        strcpy(array[i].key, str1);
        strcpy(array[i].value, str2 ? str2 : "");
    }
    fclose(fp);
}

// restrict: 두 포인터가 같은 메모리를 가리키지 않음
void swap(record *restrict a, record *restrict b) {
    record temp = *a;
    *a = *b;
    *b = temp;
}

// 삽입 정렬
void insertion_sort(record array[static WORD_COUNT]) {
    record buf;
    int i, j;

    for (i = 1; i < WORD_COUNT; i++) {
        buf = array[i]; // 임시 변수에 저장
        for (j = i-1; j >= 0 && strcmp(array[j].key, buf.key) > 0; j--)
            array[j + 1] = array[j]; // 하나씩 뒤로 밀기
        array[j + 1] = buf; // 적당한 (정렬된) 위치에 삽입
    }
}

int qsort_partition(record *array, int left, int right) {
    record pivot = array[left];
    int low = left;
    int high = right + 1;

    do {
        do low++; while (low <= right && strcmp(array[low].key, pivot.key) <= 0);
        do high--; while (high >= left && strcmp(array[high].key, pivot.key) > 0);

        if (low < high)
            swap(&array[low], &array[high]);
    } while (low < high);

    swap(&array[left], &array[high]);
    return high;
}

// 퀵 정렬
void quick_sort(record array[static WORD_COUNT]) {
    int stack[STACK_SIZE];
    int top = -1;

    stack[++top] = 0;
    stack[++top] = WORD_COUNT - 1;

    while (top >= 0) {
        int right = stack[top--];
        int left = stack[top--];
        int pivot = qsort_partition(array, left, right);

        // 함수 호출 시 stack에 parameter가 쌓이는 것을 구현
        if (left < pivot - 1) {
            // quick_sort(array, left, pivot - 1);
            stack[++top] = left;
            stack[++top] = pivot - 1;
        }
        if (pivot + 1 < right) {
            // quick_sort(array, pivot + 1, right);
            stack[++top] = pivot + 1;
            stack[++top] = right;
        }
    }
}

void hsort_heapify(record *array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && strcmp(array[left].key, array[largest].key) > 0)
        largest = left;

    if (right < n && strcmp(array[right].key, array[largest].key) > 0)
        largest = right;

    if (largest != i) {
        swap(&array[i], &array[largest]);
        hsort_heapify(array, n, largest);
    }
}

void heap_sort(record array[static WORD_COUNT]) {
    for (int i = WORD_COUNT / 2 - 1; i >= 0; i--)
        hsort_heapify(array, WORD_COUNT, i);

    for (int i = WORD_COUNT - 1; i >= 0; i--) {
        swap(&array[0], &array[i]);
        hsort_heapify(array, i, 0);
    }
}