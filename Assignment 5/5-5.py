"""
    과제 5-(5) 트리 & 그래프

    지하철 짧은 길 찾기
"""

stations = {}
with open('subway_20234748.txt') as f:
    next(f) # 호선,역 이름,이전 역,이전 거리,다음 역,다음 거리,환승 가능 호선
    for line in f.readlines():
        line, name, prev, p_dist, next, n_dist, transfer = line.strip().split(',')
        if name not in stations:
            stations[name] = []
        transfer = None if transfer == '' else [int(x) for x in transfer.split(':')]
        if prev:
            stations[name].append((
                int(line),
                None if prev == '' else prev,
                None if p_dist == '' else float(p_dist),
                transfer
            ))
        if next:
            stations[name].append((
                int(line),
                None if next == '' else next,
                None if n_dist == '' else float(n_dist),
                transfer
            ))

print('데이터 읽기 완료. 총 역의 개수: ', len(stations))

origin = input('출발역 > ')
assert origin in stations, '그런 역은 없습니다.'

destination = input('도착역 > ')
assert destination in stations, '그런 역은 없습니다.'

# Dijkstra 알고리즘
#   모든 거리를 무한대로 (아무 역도 연결되지 않음)
distances = {station: float('inf') for station in stations}
distances[origin] = 0
previous = {station: None for station in stations}
visited = set()

# 다 방문하기 전까지
while len(visited) < len(stations):
    # choose: 방문하지 않은 역 중 가장 가까운 역
    current = min((station for station in stations if station not in visited), key=lambda x: distances[x])
    visited.add(current) # 방문했음!

    for line, station, distance, transfer in stations[current]:
        if station in visited: # 방문했다면 또 갈 필요는 없지
            continue

        # 환승
        if distances[current] + distance < distances[station]:
            distances[station] = distances[current] + distance
            previous[station] = current

# 경로 출력
path = []
current = destination
while current:
    path.append(current)
    current = previous[current]

# 결과 출력
print(f'최단 거리: {distances[destination]:.1f}km')
print(f'최단 경로: {" -> ".join(reversed(path))}')