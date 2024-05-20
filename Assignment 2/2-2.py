"""
    2-(2) 계산기
 
    20234748 나선우
"""

def is_operator(char):
    return char in ['+', '-', '*', '/', '^^']

def precedence(operator):
    if operator == '+' or operator == '-':
        return 1
    elif operator == '*' or operator == '/':
        return 2
    elif operator == '^^':
        return 3

def infix_to_postfix(expression):
    postfix = []
    stack = []
    error_index = None
       
    i = 0
    while i < len(expression):
        # print(postfix)
        char = expression[i]
        if char.isdigit() or char == '.':
            start = i
            while i < len(expression) and (expression[i].isdigit() or expression[i] == '.'):
                i += 1
            number = expression[start:i]
            if '.' in number and number.count('.') > 1:
                error_index = start + number[1:].index('.') + 3
                break
            postfix.append(number)
            continue
        elif char == '(':
            stack.append((char, i))
        elif char == ')':
            if not stack:
                error_index = i
                break
            while stack and stack[-1][0] != '(':
                postfix.append(stack.pop()[0])
            if not stack:
                error_index = i
                break
            stack.pop()
        elif is_operator(char):
            while stack and precedence(stack[-1][0]) >= precedence(char):
                postfix.append(stack.pop()[0])
            stack.append((char, i))
        else:
            error_index = i
            break
        i += 1
    
    while stack:
        if stack[-1][0] == '(':
            error_index = stack[-1][1]
            break
        postfix.append(stack.pop()[0])
    
    if error_index is not None:
        return " " * (error_index) + "^ 이 위치에 오류가 있습니다."
    
    return postfix

def evaluate_postfix(postfix):
    stack = []
    for char in postfix:
        if char.isdigit() or char == '.':
            stack.append(float(char))
        elif is_operator(char):
            operand2 = stack.pop()
            operand1 = stack.pop()
            if char == '+':
                stack.append(operand1 + operand2)
            elif char == '-':
                stack.append(operand1 - operand2)
            elif char == '*':
                stack.append(operand1 * operand2)
            elif char == '/':
                if operand2 == 0:
                    return "0으로 나누면 큰일납니다."
                stack.append(operand1 / operand2)
            elif char == '^^':
                stack.append(operand1 ** operand2)
    if len(stack) == 1:
        if int(stack[0]) == stack[0]:
            return int(stack[0])
        return stack[0]
    else:
        return "식이 잘못되었습니다."

expression = input()
postfix = infix_to_postfix(expression)
print("=", evaluate_postfix(postfix))