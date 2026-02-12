#include <cstring>
#include <iostream>
using namespace std;

constexpr int dy[2][6] = {{-1, -1, 0, 1, 0, -1}, {-1, 0, 1, 1, 1, 0}};
constexpr int dx[6] = {0, 1, 1, 0, -1, -1};

int ret;
int n, m;
int honeycomb[16][16];
int visited[16][16];

void init()
{
    ret = 0;
    memset(visited, false, sizeof(visited));
}

void input()
{
    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> honeycomb[y][x];
        }
    }
}

void other(int y, int x, int dir)
{
    int tmp = honeycomb[y][x];
    for (int i = dir; i < 6; i += 2)
    {
        int ny = y + dy[x % 2][i];
        int nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx)
            return;
        tmp += honeycomb[ny][nx];
    }
    if (ret < tmp)
        ret = tmp;
}

void dfs(int cnt, int cy, int cx, int total)
{
    if (cnt == 4)
    {
        if (ret < total)
            ret = total;
        return;
    }
    for (int i = 0; i < 6; ++i)
    {
        int ny = cy + dy[cx % 2][i];
        int nx = cx + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx || visited[ny][nx])
            continue;
        visited[ny][nx] = true;
        dfs(cnt + 1, ny, nx, total + honeycomb[ny][nx]);
        visited[ny][nx] = false;
    }
}

void solve()
{
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            visited[y][x] = true;
            dfs(1, y, x, honeycomb[y][x]);
            visited[y][x] = false;
            other(y, x, 0);
            other(y, x, 1);
        }
    }
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