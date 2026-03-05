#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 21e8;

int d, w, k, ret;
int board[14][21];
int used[14];

void init()
{
    memset(used, -1, sizeof(used));
}

void input()
{
    cin >> d >> w >> k;
    for (int i = 0; i < d; ++i)
        for (int j = 0; j < w; ++j)
            cin >> board[i][j];
    ret = k;
}

bool check()
{
    if (k == 1)
        return true;
    for (int j = 0; j < w; ++j)
    {
        int prev = -1, cnt = 1;
        for (int i = 0; i < d; ++i)
        {
            int cur = (used[i] == -1 ? board[i][j] : used[i]);
            if (prev == cur)
            {
                if (++cnt == k)
                    break;
            }
            else
            {
                prev = cur;
                cnt = 1;
            }
        }
        if (cnt < k)
            return false;
    }
    return true;
}

void dfs(int idx, int cnt)
{
    if (cnt >= ret)
        return;
    if (check())
        ret = cnt;
    for (int i = idx; i < d; ++i)
    {
        used[i] = 0;
        dfs(i + 1, cnt + 1);
        used[i] = 1;
        dfs(i + 1, cnt + 1);
        used[i] = -1;
    }
}

void solve()
{
    dfs(0, 0);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    int T = 1;
    cin >> T;
    init();
    for (int tc = 1; tc <= T; ++tc)
    {
        input();
        solve();
        cout << '#' << tc << ' ' << ret << '\n';
    }

    return 0;
}