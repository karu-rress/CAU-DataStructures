"""
 * sortings.py
 * 
 * 다음 과제에서 공통적으로 사용하는
 * 정렬 함수들을 정의합니다.
 * 
 * 4-(1) 사전 파일 정렬하기
 * 4-(3) 내장된 정렬 방법과 비교하기
"""

from enum import Enum
import time

class sort_type(Enum):
    INSERTION_SORT = 1
    QUICK_SORT = 2
    HEAP_SORT = 3

class sorter:
    WORD_COUNT = 48406

    def __init__(self):
        self.array: list[(str, str)] = []
        self.load()

    def load(self):
        with open('randdict_utf8.TXT', 'r', encoding='UTF-8') as f:
            for line in f:
                k, v = line.split(" : ")
                self.array.append((k.strip(), v.strip()))

    def sort(self, type: sort_type):
        match type:
            case sort_type.INSERTION_SORT:
                start = time.time()
                self.insertion()
                end = time.time()
            case sort_type.QUICK_SORT:
                start = time.time()
                self.quick()
                end = time.time()
            case sort_type.HEAP_SORT:
                start = time.time()
                self.heap()
                end = time.time()
        
        # 정렬 검증
        self.check_sorted()

        match type:
            case sort_type.INSERTION_SORT:  print("삽입 정렬 완료")
            case sort_type.QUICK_SORT:      print("퀵 정렬 완료")
            case sort_type.HEAP_SORT:       print("힙 정렬 완료")
        
        return end - start

    def check_sorted(self):
        # 정렬 검증 (Pythonic Way)
        assert all(self.array[i][0] <= self.array[i + 1][0] for i in range(self.WORD_COUNT - 1))

    def insertion(self):
        for i in range(1, self.WORD_COUNT):
            buf = self.array[i] # 임시 변수에 저장
            j = i - 1
            while j >= 0 and self.array[j][0] > buf[0]:
                self.array[j + 1] = self.array[j]  # 하나씩 뒤로 밀기
                j -= 1
            self.array[j + 1] = buf  # 정렬된 위치에 삽입

    def quick_partition(self, left: int, right: int) -> int:
        pivot = self.array[left]
        low = left + 1
        high = right

        while True:
            while low <= right and self.array[low][0] < pivot[0]:
                low += 1
            while high > left and self.array[high][0] > pivot[0]:
                high -= 1
            if low >= high:
                break
            self.array[low], self.array[high] = self.array[high], self.array[low]
            low, high = low + 1, high - 1
        
        self.array[left], self.array[high] = self.array[high], self.array[left]
        return high

    def quick(self):
        # C언어에서 스택을 사용했으므로, 파이썬에서도 동일하게 구현
        stack = []

        stack.append(0)
        stack.append(self.WORD_COUNT - 1)

        while stack: # 값이 있는 동안
            right: int = stack.pop()
            left: int = stack.pop()
            pivot: int = self.quick_partition(left, right)

            if left < pivot - 1:
                # quick_sort(array, left, pivot - 1);
                stack.append(left)
                stack.append(pivot - 1)
            if pivot + 1 < right:
                # quick_sort(array, pivot + 1, right);
                stack.append(pivot + 1)
                stack.append(right)

    def hsort_heapify(self, n, i):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2

        if left < n and self.array[left][0] > self.array[largest][0]:
            largest = left

        if right < n and self.array[right][0] > self.array[largest][0]:
            largest = right

        if largest != i:
            self.array[i], self.array[largest] = self.array[largest], self.array[i]
            self.hsort_heapify(n, largest)

    def heap(self):
        for i in range(self.WORD_COUNT // 2 - 1, -1, -1):
            self.hsort_heapify(self.WORD_COUNT, i)

        for i in range(self.WORD_COUNT - 1, -1, -1):
            self.array[0], self.array[i] = self.array[i], self.array[0]
            self.hsort_heapify(i, 0)