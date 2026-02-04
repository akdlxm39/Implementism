#include <cmath>
#include <iostream>

using namespace std;

int ret;
int n, arr[10], total;
bool visited[10];

int factorial[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
int power[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

void input()
{
    ret = 0;
    total = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        total += arr[i];
    }
}

void dfs(int cnt, int left, int right, int rest)
{
    if (left >= right + rest)
    {
        ret += factorial[n - cnt] * power[n - cnt];
        return;
    }
    for (int i = 0; i < n; ++i)
    {
        if (visited[i])
            continue;
        visited[i] = true;
        dfs(cnt + 1, left + arr[i], right, rest - arr[i]);
        if (left >= right + arr[i])
            dfs(cnt + 1, left, right + arr[i], rest - arr[i]);
        visited[i] = false;
    }
}

void solve()
{
    dfs(0, 0, 0, total);
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
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}