#include <cstring>
#include <iostream>
using namespace std;

int ret;
int n, m, c;
int honey[10][10];
int price[10][10];
int profit[10][10];

void init()
{
    ret = 0;
    memset(profit, -1, sizeof(profit));
}

void input()
{
    cin >> n >> m >> c;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> honey[y][x];
            price[y][x] = honey[y][x] * honey[y][x];
        }
    }
}

void dfs_profit(int y, int x, int cnt, int honey_sum, int profit_sum)
{
    if (cnt == m)
    {
        if (profit[y][x] < profit_sum)
            profit[y][x] = profit_sum;
        return;
    }
    if (honey_sum + honey[y][x + cnt] <= c)
        dfs_profit(y, x, cnt + 1, honey_sum + honey[y][x + cnt], profit_sum + price[y][x + cnt]);
    dfs_profit(y, x, cnt + 1, honey_sum, profit_sum);
}

void dfs(int y, int x, int cnt, int total_profit)
{
    if (cnt == 2)
    {
        if (ret < total_profit)
            ret = total_profit;
        return;
    }
    if (x >= n)
    {
        y++;
        x = 0;
    }
    if (y == n)
        return;
    if (x + m <= n)
        dfs(y, x + m, cnt + 1, total_profit + profit[y][x]);
    dfs(y, x + 1, cnt, total_profit);
}

void solve()
{
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n - m + 1; ++x)
        {
            dfs_profit(y, x, 0, 0, 0);
        }
    }
    dfs(0, 0, 0, 0);
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