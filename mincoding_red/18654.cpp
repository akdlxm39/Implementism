#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int ret;
int n, m, cnt;
vector<int> adj_list[2][501];
bool visited[501];

void init()
{
    ret = 0;
}

void input()
{
    cin >> n >> m;
    for (int i = 0; i < 2; ++i)
        for (int j = 1; j <= n; ++j)
            adj_list[i][j].clear();
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        adj_list[0][a].push_back(b);
        adj_list[1][b].push_back(a);
    }
}

void dfs(int cur, int is_reversed)
{
    for (int nxt : adj_list[is_reversed][cur])
    {
        if (visited[nxt])
            continue;
        cnt++;
        visited[nxt] = true;
        dfs(nxt, is_reversed);
    }
}

void solve()
{
    for (int i = 1; i <= n; ++i)
    {
        cnt = 0;
        memset(visited, false, sizeof(visited));
        visited[i] = true;
        dfs(i, 0);
        dfs(i, 1);
        if (cnt == n - 1)
            ret++;
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
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}