#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct Node
{
    int y, x, cost;
};
struct cmp
{
    bool operator()(Node a, Node b)
    {
        return a.cost > b.cost;
    }
};

int n, m;
int map_[101][101], dist[101][101];

void input()
{
    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> map_[y][x];
            dist[y][x] = 21e8;
        }
    }
}

void solve()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({0, 0, map_[0][0]});
    dist[0][0] = map_[0][0];
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (dist[cur.y][cur.x] < cur.cost)
            continue;
        for (int i = 0; i < 4; ++i)
        {
            Node nxt = {cur.y + dy[i], cur.x + dx[i], cur.cost};
            if (nxt.y < 0 || n <= nxt.y || nxt.x < 0 || m <= nxt.x)
                continue;
            nxt.cost += map_[nxt.y][nxt.x];
            if (dist[nxt.y][nxt.x] <= nxt.cost)
                continue;
            dist[nxt.y][nxt.x] = nxt.cost;
            pq.push(nxt);
        }
    }
    cout << dist[n - 1][m - 1] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}