#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m, ans;
bool adj_matrix[11][11];
bool visited[11];

int dfs(int cur, int dist)
{
    visited[cur] = true;
    int ret = dist;
    for (int nxt = 1; nxt <= n; ++nxt)
        if (adj_matrix[cur][nxt] && !visited[nxt])
            ret = max(ret, dfs(nxt, dist + 1));
    visited[cur] = false;
    return ret;
}

void init()
{
    memset(adj_matrix, false, sizeof(adj_matrix));
    memset(adj_matrix[0], true, sizeof(adj_matrix[0]));
}

void input()
{
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj_matrix[u][v] = adj_matrix[v][u] = true;
    }
}

void solve()
{
    ans = dfs(0, 0);
}

void output(int testCase)
{
    cout << '#' << testCase << ' ' << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int testCase = 1; testCase <= T; ++testCase)
    {
        init();
        input();
        solve();
        output(testCase);
    }

    return 0;
}