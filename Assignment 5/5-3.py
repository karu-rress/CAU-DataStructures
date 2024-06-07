"""
    과제 5-(3) 트리 & 그래프

    수식 트리 만들기
"""

from dataclasses import dataclass # for @dataclass

@dataclass
class Node:
    value: str
    left: 'Node' = None
    right: 'Node' = None

# 중위 표기법을 후위 표기법으로 변환하는 함수
def infix_to_postfix(expression):
    precedence = {'+': 1, '-': 1, '*': 2, '/': 2, '(': 0}
    stack = []
    postfix = []
    number = ""

    for token in expression:
        if token.isdigit() or token == '.':  # 숫자나 소수점인 경우
            number += token # 일단 수로 간주하고, 저장
        else:
            if number:
                postfix.append(number)
                number = ""

            if token in precedence:
                while stack and precedence[stack[-1]] >= precedence[token]:
                    postfix.append(stack.pop())
                stack.append(token)
            elif token == '(':
                stack.append(token)
            elif token == ')':
                while stack and stack[-1] != '(':
                    postfix.append(stack.pop())
                stack.pop()  # '(' 제거

    if number:  # 마지막 숫자 추가
        postfix.append(number)

    while stack:  # 스택에 남아있는 모든 연산자를 pop
        postfix.append(stack.pop())

    return ' '.join(postfix) # 띄어쓰기 구분으로 변환

# 트리를 생성하는 함수
def make_tree(postfix):
    stack = [] # subroot만 담아도 subtree 전체가 담기는 효과

    for token in postfix:
        if token.replace('.','',1).isdigit(): # 수인가?
            stack.append(Node(token))  # 그럼 일단 노드 생성
        else: # 연산자인가?
            right = stack.pop() # 서브트리 꺼내
            left = stack.pop() # 반대쪽도 꺼내
            stack.append(Node(token, left, right)) # 연결해서 다시 넣기
    return stack.pop()

# 중위순회: 중위표기법
def inorder(root):
    stack = []
    result = ''

    while True:
        while root:
            stack.append(root)
            root = root.left

        if not stack:
            break

        node = stack.pop()
        result += f'{node.value} '
        root = node.right
    return result

# 전위순회: 전위표기법
def preorder(root):
    stack = [root]
    result = ''
    
    while stack:
        node = stack.pop()
        result += f'{node.value} '
        
        if node.right:
            stack.append(node.right)
        if node.left:
            stack.append(node.left)
    return result

# 후위순회: 후위표기법
def postorder(root):
    stack1 = [root]
    stack2 = []
    result = ''
    
    while stack1:
        node = stack1.pop()
        stack2.append(node)
        
        if node.left:
            stack1.append(node.left)
        if node.right:
            stack1.append(node.right)
    
    while stack2:
        node = stack2.pop()
        result += f'{node.value} '
    return result


# 레벨순회
def level(node):
    queue = [node] # 순회해야 할 큐
    result = ''

    while queue:
        node = queue.pop(0) # dequeue 후
        result += f'{node.value} '
        if node.left: # 자식이 있으면 enqueue
            queue.append(node.left)
        if node.right:
            queue.append(node.right)

    return result

# 결과값 계산
def calculate(node):
    if node.value.replace('.','',1).isdigit():
        return float(node.value)
    left = calculate(node.left)
    right = calculate(node.right)
    if node.value == '+':
        return left + right
    elif node.value == '-':
        return left - right
    elif node.value == '*':
        return left * right
    elif node.value == '/':
        return left / right


infix = input('수식> ')
postfix = infix_to_postfix(infix)
tree = make_tree(postfix.split())

print(f'전위표기: {preorder(tree)}')
print(f'중위표기: {inorder(tree)}')
print(f'후위표기: {postorder(tree)}')
print(f'레벨순회: {level(tree)}')
print(f'결과: {calculate(tree)}')