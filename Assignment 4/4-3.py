"""
    과제 4-(3) 정렬

    내장된 정렬 방법과 비교하기
"""

from sortings import sorter
import time

import numpy as np
from numba import jit

if __name__ == "__main__":
    # 1. Python 기본 제공 정렬
    s = sorter()
    start = time.time()
    s.array.sort(key=lambda x: x[0]) # key를 중심으로 sort
    builtin = time.time() - start
    s.check_sorted()
    
    # 2. 새로 만든 퀵 정렬
    s = sorter()
    start = time.time()
    s.quick()
    my = time.time() - start
    s.check_sorted()

    # 3. 외부 라이브러리(NumPy) 사용
    s = sorter()
    s.array = np.array(s.array, dtype=[('key', 'U30'), ('value', 'U50')])
    start = time.time()
    s.array.sort(order='key')
    numpy_time = time.time() - start
    s.check_sorted()

    print(f"Python 기본 제공 정렬: {builtin:.3f}초")
    print(f"새로 만든 퀵 정렬: {my:.3f}초")
    print(f"NumPy 정렬: {numpy_time:.3f}초")