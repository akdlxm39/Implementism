#include <climits>
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
    bool operator()(const Node &a, const Node &b) const
    {
        return a.cost > b.cost;
    }
};

int ret;
int n, m;
int map_[31][31];
vector<Node> tunnel[31][31];
int dist[31][31];

void init()
{
    ret = 0;
}

void input()
{
    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> map_[y][x];
            dist[y][x] = INT_MAX;
        }
    }
    for (int i = 0; i < m; ++i)
    {
        int ay, ax, by, bx, c;
        cin >> ay >> ax >> by >> bx >> c;
        tunnel[ay][ax].push_back({by, bx, c});
        tunnel[by][bx].push_back({ay, ax, c});
    }
}

int dijkstra()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (dist[cur.y][cur.x] < cur.cost)
            continue;
        if (cur.y == n - 1 && cur.x == n - 1)
            return cur.cost;
        for (Node nxt : tunnel[cur.y][cur.x])
        {
            if (dist[nxt.y][nxt.x] <= nxt.cost + cur.cost)
                continue;
            dist[nxt.y][nxt.x] = nxt.cost + cur.cost;
            pq.push(nxt);
        }
        for (int i = 0; i < 4; ++i)
        {
            Node nxt = {cur.y + dy[i], cur.x + dx[i], cur.cost};
            if (nxt.y < 0 || n <= nxt.y || nxt.x < 0 || n <= nxt.x)
                continue;
            int gap = map_[nxt.y][nxt.x] - map_[cur.y][cur.x];
            if (gap == 0)
                nxt.cost += 1;
            else if (gap > 0)
                nxt.cost += gap * 2;
            if (dist[nxt.y][nxt.x] <= nxt.cost)
                continue;
            dist[nxt.y][nxt.x] = nxt.cost;
            pq.push(nxt);
        }
    }
    return -1;
}

void solve()
{
    ret = dijkstra();
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