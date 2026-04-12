from collections import deque


def solve():
    n = int(input())
    grid = []
    start_y, start_x = -1, -1

    for i in range(n):
        row = input()
        grid.append(row)
        if "2" in row:
            start_y, start_x = i, row.index("2")

    q = deque([(start_y, start_x, 0)])
    visited = [[False] * n for _ in range(n)]
    visited[start_y][start_x] = True
    DIR = ((-1, 0), (1, 0), (0, -1), (0, 1))
    while q:
        y, x, dist = q.popleft()
        for dy, dx in DIR:
            ny, nx = y + dy, x + dx
            if 0 <= ny < n and 0 <= nx < n and not visited[ny][nx]:
                if grid[ny][nx] == "3":
                    return dist
                if grid[ny][nx] != "1":
                    visited[ny][nx] = True
                    q.append((ny, nx, dist + 1))
    return 0


def main():
    for tc in range(1, int(input()) + 1):
        ans = solve()
        print(f"#{tc} {ans}")


if __name__ == "__main__":
    main()
