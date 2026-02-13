#include <iostream>
using namespace std;

struct Point
{
    int y, x;
};

int ret;
int n, num;
Point pos[10];
int dist[10][10];
int status[5];

void init()
{
    ret = 21e8;
    num = 0;
}

void input()
{
    cin >> n;
    int a;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> a;
            if (a > 0)
            {
                pos[a] = {y, x};
                num++;
            }
            else if (a < 0)
                pos[4 - a] = {y, x};
        }
    }
}

void dfs(int cur, int cnt, int total_dist)
{
    if (cnt == num * 2)
    {
        if (ret > total_dist)
            ret = total_dist;
        return;
    }
    for (int nxt = 1; nxt <= num; ++nxt)
    {
        if (status[nxt] == 0)
        {
            status[nxt] = 1;
            dfs(nxt, cnt + 1, total_dist + dist[cur][nxt]);
            status[nxt] = 0;
        }
        if (status[nxt] == 1)
        {
            status[nxt] = 2;
            dfs(nxt + 4, cnt + 1, total_dist + dist[cur][nxt + 4]);
            status[nxt] = 1;
        }
    }
}

void solve()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            dist[i][j] = dist[j][i] = abs(pos[i].y - pos[j].y) + abs(pos[i].x - pos[j].x);
    dfs(0, 0, 0);
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