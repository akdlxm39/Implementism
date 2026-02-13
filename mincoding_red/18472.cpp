#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int y, x;
};

int ret;
int num;
int board[10][10];
bool attached[10][10];
int paper[6] = {0, 5, 5, 5, 5, 5};

vector<Point> v;

void init()
{
    ret = INT_MAX;
    v.clear();
}

void input()
{
    for (int y = 0; y < 10; ++y)
    {
        for (int x = 0; x < 10; ++x)
        {
            cin >> board[y][x];
            if (board[y][x])
                v.push_back({y, x});
        }
    }
}

bool check(int y, int x, int sz)
{
    for (int i = 0; i < sz; ++i)
    {
        for (int j = 0; j < sz; ++j)
        {
            if (attached[y + i][x + j])
                return false;
        }
    }
    return true;
}

void toggle(int y, int x, int sz, bool flag)
{
    for (int i = 0; i < sz; ++i)
    {
        for (int j = 0; j < sz; ++j)
        {
            attached[y + i][x + j] = flag;
        }
    }
    if (flag)
    {
        paper[sz]--;
    }
    else
    {
        paper[sz]++;
    }
}

void dfs(int cur, int cnt)
{
    if (cnt >= ret)
        return;
    for (int i = cur; i < v.size(); ++i)
    {
        if (!attached[v[i].y][v[i].x])
        {
            for (int sz = board[v[i].y][v[i].x]; sz > 0; --sz)
            {
                if (paper[sz] && check(v[i].y, v[i].x, sz))
                {
                    toggle(v[i].y, v[i].x, sz, true);
                    dfs(i + 1, cnt + 1);
                    toggle(v[i].y, v[i].x, sz, false);
                }
            }
            return;
        }
    }
    // for (int i = 1; i <= 5; ++i)
    //     cout << paper[i] << ' ';
    // cout << '\n';
    // for (int i = 0; i < 10; ++i)
    // {
    //     for (int j = 0; j < 10; ++j)
    //     {
    //         cout << board[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    if (ret > cnt)
        ret = cnt;
}

void solve()
{
    for (int y = 8; y >= 0; --y)
    {
        for (int x = 8; x >= 0; --x)
        {
            if (board[y][x] == 0)
                continue;
            int min_val = min(4, board[y + 1][x + 1]);
            min_val = min(min_val, board[y + 1][x]);
            min_val = min(min_val, board[y][x + 1]);
            board[y][x] = min_val + 1;
        }
    }

    dfs(0, 0);
    if (ret == INT_MAX)
        ret = -1;
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