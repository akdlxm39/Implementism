#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int dy[5] = {0, -1, 0, 1, 0}, dx[5] = {0, 0, 1, 0, -1};

struct Point
{
    int y;
    int x;
};

int m, a, answer;
int map_[11][11];
int charger[9];
int move_dir[2][101];
Point cur[2];

void charge_range(int y, int x, int c, int mask)
{
    queue<Point> q, nxt_q;
    map_[y][x] |= mask;
    q.push({y, x});
    while (c--)
    {
        while (!q.empty())
        {
            Point cur = q.front();
            q.pop();
            for (int i = 1; i <= 4; ++i)
            {
                int ny = cur.y + dy[i], nx = cur.x + dx[i];
                if (ny < 1 || 10 < ny || nx < 1 || 10 < nx || map_[ny][nx] & mask)
                    continue;
                map_[ny][nx] |= mask;
                nxt_q.push({ny, nx});
            }
        }
        swap(q, nxt_q);
    }
}

void input()
{
    answer = 0;
    memset(map_, 0, sizeof(map_));
    cin >> m >> a;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> move_dir[i][j];
        }
    }
    for (int i = 0; i < a; ++i)
    {
        int y, x, c, p;
        cin >> x >> y >> c >> p;
        charger[i] = p;
        charge_range(y, x, c, 1 << i);
    }

    cur[0] = {1, 1};
    cur[1] = {10, 10};
}

int max_charge(int mask1, int mask2)
{
    int ret = 0;
    if (mask1 && mask2)
    {
        for (int i = 0; i < a; ++i)
        {
            if (!(mask1 & (1 << i)))
                continue;
            for (int j = 0; j < a; ++j)
            {
                if (!(mask2 & (1 << j)))
                    continue;
                if (i == j)
                    ret = max(ret, charger[i]);
                else
                    ret = max(ret, charger[i] + charger[j]);
            }
        }
    }
    else if (mask1)
    {
        for (int i = 0; i < a; ++i)
        {
            if (!(mask1 & (1 << i)))
                continue;
            ret = max(ret, charger[i]);
        }
    }
    else if (mask2)
    {
        for (int i = 0; i < a; ++i)
        {
            if (!(mask2 & (1 << i)))
                continue;
            ret = max(ret, charger[i]);
        }
    }
    return ret;
}

void solve()
{
    for (int i = 0; i <= m; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            cur[j].y += dy[move_dir[j][i]];
            cur[j].x += dx[move_dir[j][i]];
        }
        answer += max_charge(map_[cur[0].y][cur[0].x], map_[cur[1].y][cur[1].x]);
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
        input();
        solve();
        cout << "#" << tc << " " << answer << '\n';
    }

    return 0;
}