#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int ret;
int n, m;
vector<vector<int>> adj_list;
vector<bool> visited;

void init()
{
    ret = 0;
}

void input()
{
    cin >> n >> m;
    adj_list.assign(n + 1, vector<int>());
    visited.assign(n + 1, false);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
}

void solve()
{
    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (visited[i])
            continue;
        q.push(i);
        visited[i] = true;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int nxt : adj_list[cur])
            {
                if (visited[nxt])
                    continue;
                visited[nxt] = true;
                q.push(nxt);
            }
        }
        ret++;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        init();
        input();
        solve();
        cout << '#' << tc << ' ' << ret << '\n';
    }

    return 0;
}