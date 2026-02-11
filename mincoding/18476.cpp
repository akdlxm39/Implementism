#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

constexpr int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

int ret;
int n, sy, sx;
int board[51][51];
bool visited[51][51];

void init()
{
    ret = 0;
    memset(visited, false, sizeof(visited));
}

void input()
{
    cin >> n;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> board[y][x];
            if (board[y][x] == 2)
                sy = y, sx = x;
        }
    }
}

void dfs(int y, int x, int cnt)
{
    if (cnt == 3)
        return;
    for (int i = 0; i < 4; ++i)
    {
        bool jump = false;
        for (int l = 1; l < n; ++l)
        {
            int ny = y + dy[i] * l, nx = x + dx[i] * l;
            if (ny < 0 || n <= ny || nx < 0 || n <= nx)
                break;
            if (!jump)
            {
                if (board[ny][nx] == 1)
                    jump = true;
                continue;
            }
            if (board[ny][nx] == 1)
            {
                if (!visited[y][x])
                {
                    visited[y][x] = true;
                    ret++;
                }
                board[ny][nx] = 0;
                dfs(ny, nx, cnt + 1);
                board[ny][nx] = 1;
                break;
            }
            dfs(ny, nx, cnt + 1);
        }
    }
}

void solve()
{
    dfs(sy, sx, 0);
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