#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int dy[4] = {-1, 0, 0, 1}, dx[4] = {0, -1, 1, 0};

struct Node
{
    int y, x, dist;
};

int n, sy, sx, level, experience, cnt, answer;
int map_[21][21], visited[21][21];

void input()
{
    level = 2;
    experience = 0;
    cnt = 1;
    cin >> n;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> map_[y][x];
            if (map_[y][x] == 9)
            {
                sy = y, sx = x;
                map_[y][x] = 0;
            }
        }
    }
}

void bfs()
{
    queue<Node> q;
    Node candidate = {21, 21, -1};
    q.push({sy, sx, 0});
    visited[sy][sx] = cnt;
    while (!q.empty())
    {
        queue<Node> nxt_q;
        while (!q.empty())
        {
            Node cur = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i)
            {
                Node nxt = {cur.y + dy[i], cur.x + dx[i], cur.dist + 1};
                if (nxt.y < 0 || n <= nxt.y || nxt.x < 0 || n <= nxt.x || visited[nxt.y][nxt.x] == cnt ||
                    map_[nxt.y][nxt.x] > level)
                    continue;
                if (map_[nxt.y][nxt.x] != 0 && map_[nxt.y][nxt.x] < level)
                {
                    if (candidate.y > nxt.y)
                        candidate = nxt;
                    else if (candidate.y == nxt.y && candidate.x > nxt.x)
                        candidate = nxt;
                }
                nxt_q.push(nxt);
                visited[nxt.y][nxt.x] = cnt;
            }
        }
        if (candidate.dist != -1)
        {
            q.push(candidate);
            visited[candidate.y][candidate.x] = ++cnt;
            map_[candidate.y][candidate.x] = 0;
            answer = candidate.dist;
            if (++experience == level)
            {
                level++;
                experience = 0;
            }
            candidate = {21, 21, -1};
        }
        else
        {
            q.swap(nxt_q);
        }
    }
}

void solve()
{
    bfs();
    cout << answer << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}