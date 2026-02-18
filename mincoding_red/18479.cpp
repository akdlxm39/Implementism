#include <iostream>
using namespace std;

int ret;
int n, p;
int arr[2][21];

void init()
{
    ret = 0;
}

void input()
{
    cin >> n >> p;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> arr[i][j];
        }
    }
}

void dfs(int cur, int total, int prev)
{
    if (cur == n)
    {
        if (ret < total)
            ret = total;
        return;
    }
    for (int i = 0; i < 2; ++i)
    {
        if (prev == i)
            dfs(cur + 1, total + arr[i][cur] - p, i);
        else
            dfs(cur + 1, total + arr[i][cur], i);
    }
}

void solve()
{
    dfs(0, 0, -1);
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