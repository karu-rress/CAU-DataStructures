"""
    과제 4-(1) 정렬

    사전 파일 정렬 (삽입/퀵/힙)
"""

from sortings import sorter, sort_type
    
if __name__ == "__main__":
    is_time = sorter().sort(sort_type.INSERTION_SORT)
    qs_time = sorter().sort(sort_type.QUICK_SORT)
    hs_time = sorter().sort(sort_type.HEAP_SORT)

    print(f"삽입 정렬: {is_time:.3f}초")
    print(f"퀵 정렬: {qs_time:.3f}초")
    print(f"힙 정렬: {hs_time:.3f}초")