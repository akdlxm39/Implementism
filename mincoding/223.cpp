#include <iostream>
#include <queue>
using namespace std;

constexpr int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2}, dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};

struct Point
{
    int y;
    int x;
    int move;
};

int n, m;
int sy, sx, ey, ex;
bool visited[101][101];

void input()
{
    cin >> n >> m;
    cin >> sy >> sx;
    cin >> ey >> ex;
}

int bfs()
{
    queue<Point> q;
    q.push({sy, sx, 0});
    while (!q.empty())
    {
        int cy = q.front().y;
        int cx = q.front().x;
        int move = q.front().move;
        q.pop();

        for (int i = 0; i < 8; ++i)
        {
            int ny = cy + dy[i], nx = cx + dx[i];
            if (ny < 1 || n < ny || nx < 1 || m < nx || visited[ny][nx])
                continue;
            if (ny == ey && nx == ex)
                return move + 1;

            visited[ny][nx] = true;
            q.push({ny, nx, move + 1});
        }
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    cout << bfs() << '\n';

    return 0;
}