#include <iostream>
#include <queue>
using namespace std;

constexpr int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct Point
{
    int y, x;
};

int sy, sx;
int map_[5][5];

void bfs(int y, int x)
{
    queue<Point> q;
    q.push({y, x});
    map_[y][x] = 1;
    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            Point nxt = {cur.y + dy[i], cur.x + dx[i]};
            if (nxt.y < 0 || 5 <= nxt.y || nxt.x < 0 || 5 <= nxt.x || map_[nxt.y][nxt.x])
                continue;
            map_[nxt.y][nxt.x] = map_[cur.y][cur.x] + 1;
            q.push(nxt);
        }
    }
}

void solve()
{
    cin >> sy >> sx;
    bfs(sy, sx);
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            cout << map_[y][x] << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}