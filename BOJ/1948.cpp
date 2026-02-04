#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, m, s, e;
vector<vector<array<int, 2>>> adj;
int in_degree[10001];

int prev_weight[10001];
vector<vector<int>> prev_cities;

bool visited[10001];

int total_time, golden_loads;

void input()
{
    cin >> n >> m;
    adj.resize(n + 1);
    prev_cities.resize(n + 1);
    for (int i = 0, u, v, w; i < m; ++i)
    {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        in_degree[v]++;
    }
    cin >> s >> e;
    return;
}

void solve()
{
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < adj[cur].size(); ++i)
        {
            int nxt = adj[cur][i][0], nxt_weight = adj[cur][i][1] + prev_weight[cur];
            if (prev_weight[nxt] < nxt_weight)
            {
                prev_weight[nxt] = nxt_weight;
                prev_cities[nxt].clear();
                prev_cities[nxt].push_back(cur);
            }
            else if (prev_weight[nxt] == nxt_weight)
            {
                prev_cities[nxt].push_back(cur);
            }
            if (--in_degree[nxt] == 0)
                q.push(nxt);
        }
    }
    total_time = prev_weight[e];
    q.push(e);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        golden_loads += prev_cities[cur].size();
        for (int i = 0; i < prev_cities[cur].size(); ++i)
        {
            int nxt = prev_cities[cur][i];
            if (visited[nxt])
                continue;
            visited[nxt] = true;
            q.push(nxt);
        }
    }

    cout << total_time << '\n' << golden_loads << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}