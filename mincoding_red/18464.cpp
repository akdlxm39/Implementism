#include <climits>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int d[2] = {-1, 1};

struct Node
{
    int y, x, limit;
};
struct cmp
{
    bool operator()(const Node &a, const Node &b) const
    {
        return a.limit > b.limit;
    }
};

int n, m, sy, sx;
int map_[51][51];
int dist[51][51];

void input()
{
    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> map_[y][x];
            if (map_[y][x] == 2)
                sy = y, sx = x;
            dist[y][x] = INT_MAX;
        }
    }
}

int dijkstra()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({sy, sx, 0});
    dist[sy][sx] = 0;
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (dist[cur.y][cur.x] < cur.limit)
            continue;
        if (map_[cur.y][cur.x] == 3)
            return cur.limit;
        for (int i = 0; i < 2; ++i)
        {
            int ny = cur.y;
            for (int l = 1; l < n; ++l)
            {
                ny += d[i];
                if (ny < 0 || n <= ny)
                    break;
                if (map_[ny][cur.x] != 0)
                {
                    int nxt_limit = max(l, cur.limit);
                    if (dist[ny][cur.x] > nxt_limit)
                    {
                        dist[ny][cur.x] = nxt_limit;
                        pq.push({ny, cur.x, nxt_limit});
                    }
                    break;
                }
            }
        }
        for (int i = 0; i < 2; ++i)
        {
            for (int nx = cur.x + d[i]; 0 <= nx && nx < m && map_[cur.y][nx] && dist[cur.y][nx] > cur.limit; nx += d[i])
            {
                dist[cur.y][nx] = cur.limit;
                pq.push({cur.y, nx, cur.limit});
            }
        }
    }
    return -1;
}

void solve()
{
    cout << dijkstra() << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}