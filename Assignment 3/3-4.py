"""
   과제 3-(4) 연결 리스트
 
   사전 개선하기 (python)
"""

from dataclasses import dataclass
from typing import Optional
import random
import time

######## 기존 LinkedList

@dataclass 
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
        if self.head is None or new.key < self.head.key:
            new.next = self.head
            self.head = new
        else:
            p = self.head
            while p.next is not None and p.next.key < new.key:
                p = p.next
            new.next = p.next
            p.next = new

    def run(self, words: list[str]):
        for w in words:
            self.search(w)

######## 개선한 LinkedList

class NewNode:
    def __init__(self, key: str, value: str, level: int):
        self.key = key
        self.value = value
        self.forward = [None] * (level + 1)

class NewLinkedList:
    MAX_LEVEL = 64 # 공간복잡도를 희생하여 시간복잡도를 높임

    def __init__(self):
        self.level = 0
        self.head = NewNode('', '', self.MAX_LEVEL) # head 노드를 별도로 관리
        with open('randdict_utf8.TXT', 'r', encoding='UTF-8') as f:
            for line in f:
                k, v = line.split(' : ')
                self.insert(k.strip(), v.strip())

    # random level 생성: 리스트를 일부 건너뛸 때 사용
    def random_level(self) -> int:
        level = 0
        while random.random() < 0.5 and level < self.MAX_LEVEL:
            level += 1
        return level

    def insert(self, key: str, value: str):
        update = [None] * (self.MAX_LEVEL + 1)
        p = self.head
        
        for i in range(self.level, -1, -1):
            while p.forward[i] and p.forward[i].key < key:
                p = p.forward[i]
            update[i] = p

        p = p.forward[0]
        level = self.random_level()
        if level > self.level:
            for i in range(self.level + 1, level + 1):
                update[i] = self.head
            self.level = level

        new_node = NewNode(key, value, level)
        for i in range(level + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node

    def search(self, key: str) -> (str | None):
        p = self.head
        for i in range(self.level, -1, -1):
            while p.forward[i] and p.forward[i].key < key:
                p = p.forward[i]
        p = p.forward[0]
        if p and p.key == key:
            return p.value
        return None

    def run(self, words: list[str]):
        for w in words:
            self.search(w)

if __name__ == "__main__":
    words = []
    with open('randdict_utf8.TXT', 'r', encoding='UTF-8') as f:
        for line in f:
            words.append(line.strip().split(' : ')[0])
    
    # 랜덤한 50000개의 단어 선택
    random_words = []
    for _ in range(50000):
        random_words.append(random.choice(words))
        
    old = LinkedList()
    new = NewLinkedList()
    
    start = time.time()
    old.run(random_words)
    end = time.time()
    
    print(f'기존 연결리스트 저장 구조: {end - start:.3f}초')
    
    start = time.time()
    new.run(random_words)
    end = time.time()

    print(f'개선한 연결리스트 저장 구조: {end - start:.3f}초')