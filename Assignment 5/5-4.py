"""
    과제 5-(4) 트리 & 그래프

    미로 분석기
"""

maze_origin = []
maze = []
row, col = 0, 0
directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]

# 미로를 0, 1의 데이터로 변환하여 저장.
file = input('미로 파일의 이름을 입력하세요 : ')
with open(file, 'r', encoding='UTF-8') as f:
    string = f.readlines()
    maze_origin = [list(x.strip()) for x in string[1:]]
    row = len(string) - 3
    col = len(string[1].strip()) - 2
    for line in string[2:-1]:
        converted = []
        for ch in line.strip()[1:-1]:
            converted.append(int(ch == ' '))
        maze.append(converted)

visited = [([False] * col) for _ in range(row)]

# 길을 찾는 함수
def bfs_find_path():
    q = [(0, 0, [])]
    visited[0][0] = True # 방문했음!
    
    while q:
        a, b, path = q.pop(0)
        if a == row - 1 and b == col - 1: # 도착했니?
            return path + [(a, b)]    # 길 알려줄게
        
        for x, y in directions: # 갈 수 있는 방향
            x, y = x + a, y + b
            if 0 <= x < row and 0 <= y < col and maze[x][y] == 1 and not visited[x][y]:
                visited[x][y] = True # 방문했음!
                q.append((x, y, path + [(a, b)]))

    return None # 길이 없어요

# 길의 개수를 찾는 함수
def dfs_find_all_paths(x, y, path):
    if x == row - 1 and y == col - 1:
        return 1 # 도착했다면 경로 하나 추가
    
    path.add((x, y)) # 방문한 점 추가
    path_count = 0
    
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < row and 0 <= ny < col and maze[nx][ny] == 1 and (nx, ny) not in path:
            path_count += dfs_find_all_paths(nx, ny, path)
    
    path.remove((x, y)) # 경로에서 제거 (백트래킹)
    return path_count

# 길 출력
def print_path(maze_origin, path):
    for x, y in path:
        # 테두리를 고려하여 표기
        if maze_origin[x + 1][y + 1] == ' ':
            maze_origin[x + 1][y + 1] = 'O'
    
    for line in maze_origin:
        print("".join(line))

path = bfs_find_path()
num_paths = dfs_find_all_paths(0, 0, set())

print('분석 결과: ', end='')
if num_paths == 0:
    print("길이 없음")
else:
    print("길이 1개 있음" if num_paths == 1 else "길이 2개 이상 있음")
    print_path(maze_origin, path)