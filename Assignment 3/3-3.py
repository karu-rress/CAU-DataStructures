"""
   과제 3-(3) 연결 리스트
 
   사전 만들기 (python)
"""

from dataclasses import dataclass
from typing import Optional

# C와 동일하게, 단일 리스트로 구현
@dataclass # C의 struct를 간편하게 구현할 수 있게 함
class Node:
    key: str
    value: str
    next: Optional['Node'] = None
    
class LinkedList:
    def __init__(self):
        self.head: (Node | None) = None
        with open('randdict_utf8.TXT', 'r', encoding='UTF-8') as f:
            for line in f:
                k, v = line.split(' : ')
                self.insert(k.strip(), v.strip())
        
    def search(self, query: str) -> (str | None):
        p = self.head
        while p is not None:
            if p.key == query:
                return p.value
            p = p.next
        return None

    def insert(self, key: str, value: str):
        new = Node(key, value)
        # 단어가 맨 앞에 오는가?
        if self.head is None or new.key < self.head.key:
            new.next = self.head
            self.head = new
        else:
            p = self.head
            while p.next is not None and p.next.key < new.key:
                p = p.next
            new.next = p.next
            p.next = new

    def run(self):
        try:
            while True:
                query = input('>> ')
                result = self.search(query)
                print(result if result is not None else '찾는 단어가 없습니다.')
        except EOFError:
            return
        
if __name__ == "__main__":
    dictionary = LinkedList()
    dictionary.run()