#include <stdio.h>
#include <stdlib.h>
#define N 10
#define for_10_times for (int i = 0; i < 10; i++)
#define sort_begin puts(__func__);

void init_array(int array[], int origin[]) {
    srand(01020304);
    for_10_times origin[i] = array[i] = rand() % 20 + 1;
}

void reload_array(int array[], int origin[]) {
    for_10_times array[i] = origin[i];
}

void print_array(int array[]) {
    for_10_times printf("%d, ", array[i]);
    printf("\b\b  \n");
}

void swap(int *pa, int *pb) {
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void insertion_sort(int array[]) {
    sort_begin
    int i, j, key;

    for (i = 1; i < N; i++) { // 0번째는 정렬되었다고 가정
        key = array[i]; // 정렬되지 않은 데이터! 를 어디에 넣을까
        for (j = i - 1; j >= 0 && array[j] > key; j--) {
            array[j + 1] = array[j]; // 덮어써도 상관 없음. 어차피 key에 저장되어 있으니.
        }
        array[j + 1] = key; // 만들어진 공간에 데이터를 넣자
    }
}

void bubble_sort(int array[]) {
    sort_begin
    for (int i = N - 1; i > 0; i--) { // i는 위에서부터 내려오고
        for (int j = 0; j < i; j++) { // j는 위에서 i까지 올라갈 동안
            if (array[j] > array[j + 1]) // 순서 잘못된 게 있으면 바꾸기
                swap(&array[j], &array[j + 1]); // 즉, 제일 큰 걸 뒤로 보내기
        }
    }
}

void selection_sort(int array[]) {
    sort_begin
    int least;

    for (int i = 0; i < N - 1; i++) {
        least = i;
        for (int j = i + 1; j < N; j++) { // 최솟값 찾기
            if (array[j] < array[least]) least = j;
        }
        swap(&array[i], &array[least]);
    }
}

void inc_insertion_sort(int array[], int first, int last, int gap) {
    int i, j, key;

    for (i = first + gap; i < last; i += gap) {
        key = array[i];
        for (j = i - gap; j >= first && array[j] > key; j -= gap) {
            array[j + gap] = array[j];
        }
        array[j + gap] = key;
    }
}
void shell_sort(int array[]) {
    sort_begin
    for (int gap = N/2; gap > 0; gap /= 2) {
        if (gap % 2 == 0) gap++;
        for (int i = 0; i < gap; i++) // 부분 리스트의 개수 |[0, gap)|
            inc_insertion_sort(array, i, N - 1, gap);
    }
}

void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1; // 왼쪽 배열 크기
    int n2 = right - mid;    // 오른쪽 배열 크기

    int leftArray[n1];
    int rightArray[n2];

    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = array[mid + 1 + j];

    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    // 합병
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j])
            array[k] = leftArray[i++];
        else
            array[k] = rightArray[j++];
        k++;
    }

    while (i < n1) array[k++] = leftArray[i++];
    while (j < n2) array[k++] = rightArray[j++];
}
void merge_sort_recursive(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_recursive(array, left, mid);
        merge_sort_recursive(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}
void merge_sort(int array[]) {
    sort_begin
    merge_sort_recursive(array, 0, N - 1);
}


int partition(int array[], int left, int right) {
    int pivot, low = left, high = right + 1;
    pivot = array[left];
    do {
        do low++; while (low <= right && array[low] < pivot); // 앞쪽에 잘못 들어간 데이터가 있나?
        do high--; while (high >= left && array[high] > pivot); // 뒤에 잘못 들어간 게 있나?
        if (low < high) swap(&array[low], &array[high]); // 어 바꿔
    } while (low < high);
    swap(&array[left], &array[high]);
    return high;
}
void quick_sort_recursive(int array[], int left, int right) {
    if (left < right) {
        int q = partition(array, left, right);
        quick_sort_recursive(array, left, q - 1);
        quick_sort_recursive(array, q + 1, right);
    }
}
void quick_sort(int array[]) {
    sort_begin
    quick_sort_recursive(array, 0, N - 1);
}

void heapify(int array[], int n, int root) {
    int largest = root; // Initialize largest as root
    int left = 2 * root + 1; // Left child
    int right = 2 * root + 2; // Right child

    if (left < n && array[left] > array[largest]) largest = left;
    if (right < n && array[right] > array[largest]) largest = right;
    if (largest != root) {
        swap(&array[root], &array[largest]);
        heapify(array, n, largest);
    }
}
void heap_sort(int array[]) {
    sort_begin
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(array, N, i);

    for (int i = N - 1; i > 0; i--) {
        swap(&array[0], &array[i]);
        heapify(array, i, 0);
    }
}

void do_sort(int array[], int origin[], void (*algorithm)(int[])) {
    reload_array(array, origin);
    algorithm(array);
    print_array(array);
}

int main() {
    int array[N], origin[N];
    
    init_array(array, origin);
    print_array(array);

    do_sort(array, origin, insertion_sort);
    do_sort(array, origin, bubble_sort);
    do_sort(array, origin, selection_sort);
    do_sort(array, origin, shell_sort);
    do_sort(array, origin, merge_sort);
    do_sort(array, origin, quick_sort);
    do_sort(array, origin, heap_sort);
}