#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

constexpr int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct Point
{
    int y;
    int x;
};

int n, m;
int board[76][76], tmp[76][76];
int cnt;
int ret = 0;
bool visited[76][76];

void input()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> board[i][j];
        }
    }
}

void bfs(int sy, int sx)
{
    queue<Point> q;
    q.push({sy, sx});
    visited[sy][sx] = true;
    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int ny = cur.y + dy[i], nx = cur.x + dx[i];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx || visited[ny][nx])
                continue;
            if (board[ny][nx] == 0)
            {
                if (tmp[cur.y][cur.x])
                    tmp[cur.y][cur.x]--;
                continue;
            }
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }
}

void solve()
{
    do
    {
        cnt = 0;
        memset(visited, false, sizeof(visited));
        memcpy(tmp, board, sizeof(board));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (board[i][j] && !visited[i][j])
                {
                    bfs(i, j);
                    cnt++;
                }
            }
        }
        ret++;
        swap(board, tmp);
    } while (cnt == 1);
    cout << (cnt ? ret - 1 : 0) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}