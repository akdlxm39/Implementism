#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge
{
    int to, cost;
};
struct Node
{
    int id, cost;
};

struct cmp
{
    bool operator()(Node a, Node b)
    {
        return a.cost > b.cost;
    }
};

int v, e, p;
vector<Edge> adj_list[5001];
int dist[5001];

void input()
{
    cin >> v >> e >> p;
    int from, to, cost;
    for (int i = 0; i < e; ++i)
    {
        cin >> from >> to >> cost;
        adj_list[from].push_back({to, cost});
        adj_list[to].push_back({from, cost});
    }
}

void dijkstra(int st)
{
    for (int i = 1; i <= v; ++i)
        dist[i] = INT_MAX;
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({st, 0});
    dist[st] = 0;
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (dist[cur.id] < cur.cost)
            continue;
        for (Edge edge : adj_list[cur.id])
        {
            Node nxt = {edge.to, cur.cost + edge.cost};
            if (dist[nxt.id] <= nxt.cost)
                continue;
            dist[nxt.id] = nxt.cost;
            pq.push(nxt);
        }
    }
}

void solve()
{
    dijkstra(1);
    int one_to_p = dist[p];
    int one_to_v = dist[v];
    if (one_to_p == INT_MAX && one_to_v == INT_MAX)
    {
        cout << "SORRY\n";
        return;
    }
    dijkstra(p);
    int p_to_v = dist[v];
    if (one_to_p + p_to_v == one_to_v)
        cout << "OKAY\n";
    else
        cout << "SORRY\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}