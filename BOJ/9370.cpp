#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 21e8;

struct Edge
{
    int to, dist;
};
struct Node
{
    int id, dist;
    inline bool operator<(const Node &other) const
    {
        return dist > other.dist;
    }
};

int n, m, t, s, g, h;
vector<Edge> adj_list[2001];
priority_queue<Node> pq;
int dist[2001];
vector<int> candi;

void solve()
{

    cin >> n >> m >> t >> s >> g >> h;
    for (int i = 1; i <= n; ++i)
    {
        adj_list[i].clear();
        dist[i] = INF;
    }
    for (int i = 0, a, b, d; i < m; ++i)
    {
        cin >> a >> b >> d;
        d = d * 2 - ((a == g && b == h) || (a == h && b == g));
        adj_list[a].push_back({b, d});
        adj_list[b].push_back({a, d});
    }
    candi.resize(t);
    for (int &x : candi)
        cin >> x;
    sort(candi.begin(), candi.end());
    pq = priority_queue<Node>();
    dist[s] = 0;
    pq.push({s, 0});
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (dist[cur.id] < cur.dist)
            continue;
        for (const Edge &e : adj_list[cur.id])
        {
            Node nxt = {e.to, cur.dist + e.dist};
            if (dist[nxt.id] <= nxt.dist)
                continue;
            dist[nxt.id] = nxt.dist;
            pq.push(nxt);
        }
    }
    for (int x : candi)
        if (dist[x] & 1)
            cout << x << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    candi.reserve(2000);

    int TC;
    cin >> TC;
    while (TC--)
        solve();

    return 0;
}