/**
 * sortings.h
 * 
 * 다음 과제에서 공통적으로 사용하는
 * 정렬 함수들을 선언합니다.
 * 
 * 4-(1) 사전 파일 정렬하기
 * 4-(2) 사전 파일 재정렬하기
 * 4-(3) 내장된 정렬 방법과 비교하기
*/

#ifndef _SORTINGS_H
#define _SORTINGS_H

// Header files
#include <assert.h> // assert()
#include <string.h> // strcmp(), strtok(), ...
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define MAX_LENGTH 100
#define WORD_COUNT 48406
#define STACK_SIZE 1000

// Structures
typedef struct {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
} record;

typedef enum {
    INSERTION_SORT,
    QUICK_SORT,
    HEAP_SORT
} sort_type;

// Function prototypes
clock_t     sort(record *array, sort_type type);
void        check_sorted(record *array);
void        load(record *array);
void        swap(record *restrict a, record *restrict b);
void        insertion_sort(record array[static WORD_COUNT]);
int         qsort_partition(record *array, int left, int right);
void        quick_sort(record array[static WORD_COUNT]);
void        hsort_heapify(record *array, int n, int i);
void        heap_sort(record array[static WORD_COUNT]);

#endif