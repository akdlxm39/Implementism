#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

constexpr int dy[4] = {-1, 1, 0, 0};
constexpr int dx[4] = {0, 0, -1, 1};
constexpr bool pipe_dir[8][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {1, 1, 0, 0}, {0, 0, 1, 1},
                                 {1, 0, 0, 1}, {0, 1, 0, 1}, {0, 1, 1, 0}, {1, 0, 1, 0}};
constexpr int reverse_dir[4] = {1, 0, 3, 2};

int ret;
int n, m, r, c, l;
int map_[51][51];
int visited[51][51];

struct Point
{
    int y, x;
};

void init()
{
    ret = 1;
    memset(visited, 0, sizeof(visited));
}

void input()
{
    cin >> n >> m >> r >> c >> l;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> map_[y][x];
        }
    }
}

void bfs()
{
    queue<Point> q;
    q.push({r, c});
    visited[r][c] = 1;
    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            if (!pipe_dir[map_[cur.y][cur.x]][i])
                continue;
            Point nxt = {cur.y + dy[i], cur.x + dx[i]};
            if (nxt.y < 0 || n <= nxt.y || nxt.x < 0 || m <= nxt.x || visited[nxt.y][nxt.x] ||
                !pipe_dir[map_[nxt.y][nxt.x]][reverse_dir[i]])
                continue;
            visited[nxt.y][nxt.x] = visited[cur.y][cur.x] + 1;
            ret++;
            if (visited[nxt.y][nxt.x] < l)
                q.push(nxt);
        }
    }
}

void solve()
{
    if (l > 1)
        bfs();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}