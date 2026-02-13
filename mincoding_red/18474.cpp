#include <iostream>
using namespace std;

constexpr int dy[3] = {0, 1, 1}, dx[3] = {1, 1, 0};

struct Pipe
{
    int y, x;
    int dir;
};

int ret;
int n;
int house[17][17];

void init()
{
    ret = 0;
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> house[i][j];
}

void dfs(Pipe cur)
{
    if (cur.y + dy[cur.dir] == n - 1 && cur.x + dx[cur.dir] == n - 1)
    {
        ret++;
        return;
    }
    if (cur.dir == 0 || cur.dir == 1)
    {
        int ny = cur.y + dy[cur.dir] + dy[0];
        int nx = cur.x + dx[cur.dir] + dx[0];
        if (0 <= ny && ny < n && 0 <= nx && nx < n)
        {
            if (house[ny][nx] == 0)
            {
                dfs({cur.y + dy[cur.dir], cur.x + dx[cur.dir], 0});
            }
        }
    }
    if (cur.dir == 1 || cur.dir == 2)
    {
        int ny = cur.y + dy[cur.dir] + dy[2];
        int nx = cur.x + dx[cur.dir] + dx[2];
        if (0 <= ny && ny < n && 0 <= nx && nx < n)
        {
            if (house[ny][nx] == 0)
            {
                dfs({cur.y + dy[cur.dir], cur.x + dx[cur.dir], 2});
            }
        }
    }
    int ny = cur.y + dy[cur.dir] + dy[1];
    int nx = cur.x + dx[cur.dir] + dx[1];
    if (0 <= ny && ny < n && 0 <= nx && nx < n)
    {
        if (house[ny][nx] == 0 && house[ny - 1][nx] == 0 && house[ny][nx - 1] == 0)
        {
            dfs({cur.y + dy[cur.dir], cur.x + dx[cur.dir], 1});
        }
    }
}

void solve()
{
    dfs({0, 0, 0});
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