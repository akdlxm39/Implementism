#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> adj_list[1'000'001];
int memo[1'000'001][2];

void input()
{
    memset(memo, -1, sizeof(memo));
    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
}

int dfs(int cur, int prev, int is_early_adapter)
{
    int ret = 0;
    if (memo[cur][is_early_adapter] != -1)
        return memo[cur][is_early_adapter];

    if (is_early_adapter)
    {
        ret++;
        for (int nxt : adj_list[cur])
        {
            if (nxt == prev)
                continue;
            ret += min(dfs(nxt, cur, true), dfs(nxt, cur, false));
        }
    }
    else
    {
        for (int nxt : adj_list[cur])
        {
            if (nxt == prev)
                continue;
            ret += dfs(nxt, cur, true);
        }
    }
    memo[cur][is_early_adapter] = ret;
    return ret;
}

void solve()
{
    cout << min(dfs(1, 0, true), dfs(1, 0, false)) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}