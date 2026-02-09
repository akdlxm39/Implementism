#include <iostream>
#include <queue>
using namespace std;

constexpr int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct Point
{
    int y;
    int x;
};

int height, width, answer;
bool visited[101][101];

void solve()
{
    cin >> height >> width;
    queue<Point> q;
    for (int i = 0; i < 2; ++i)
    {
        int y, x;
        cin >> y >> x;
        q.push({y, x});
        visited[y][x] = true;
    }
    while (!q.empty())
    {
        queue<Point> nxt_q;
        while (!q.empty())
        {
            Point cur = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i)
            {
                int ny = cur.y + dy[i], nx = cur.x + dx[i];
                if (ny < 0 || height <= ny || nx < 0 || width <= nx || visited[ny][nx])
                    continue;
                visited[ny][nx] = true;
                nxt_q.push({ny, nx});
            }
        }
        answer++;
        swap(q, nxt_q);
    }
    cout << answer << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}