#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int to;
    int cost;
};

int n, st, e, ret;
vector<Edge> adj_list[100001];

void input()
{
    cin >> n >> st >> e;
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v, c;
        cin >> u >> v >> c;
        adj_list[u].push_back({v, c});
        adj_list[v].push_back({u, c});
    }
}

bool dfs(int cur, int prev, int total_costs, int max_cost)
{
    if (cur == e)
    {
        ret = total_costs - max_cost;
        return true;
    }
    for (int i = 0; i < adj_list[cur].size(); ++i)
    {
        int nxt = adj_list[cur][i].to;
        int nxt_cost = adj_list[cur][i].cost;
        if (nxt == prev)
            continue;
        if (dfs(nxt, cur, total_costs + nxt_cost, max(max_cost, nxt_cost)))
            return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    dfs(st, 0, 0, 0);

    cout << ret << '\n';

    return 0;
}