#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge
{
    int to;
    int cost;
};

struct Node
{
    int cur;
    int total_cost;
};

int n, m, k;
vector<Edge> adj_list[11];
bool can_go[11];

void input()
{
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        adj_list[from].push_back({to, cost});
    }
}

void solve()
{
    queue<Node> q;
    q.push({0, 0});
    while (!q.empty())
    {
        Node cur = q.front();
        q.pop();
        for (Edge e : adj_list[cur.cur])
        {
            int nxt = e.to;
            int cost = e.cost;
            if (cur.total_cost + cost > k)
                continue;
            can_go[nxt] = true;
            q.push({nxt, cur.total_cost + cost});
        }
    }
    for (int i = 1; i < n; ++i)
    {
        if (can_go[i])
            cout << i << ' ';
    }
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}