#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int n, m, ans;
string map_[600];
bool visited[600][600];

struct Point
{
    int y, x;
    Point operator+(Point other) const
    {
        return {y + other.y, x + other.x};
    }
    bool isValid() const
    {
        return 0 <= y && y < n && 0 <= x && x < m && map_[y][x] != 'X' && !visited[y][x];
    }
};

const Point DIR[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void solve()
{
    cin >> n >> m;
    queue<Point> q;
    for (int i = 0; i < n; ++i)
    {
        cin >> map_[i];
        size_t j = map_[i].find('I');
        if (j != string::npos)
        {
            q.push({i, int(j)});
            visited[i][j] = true;
        }
    }
    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();
        if (map_[cur.y][cur.x] == 'P')
            ans++;
        for (Point d : DIR)
        {
            Point nxt = cur + d;
            if (nxt.isValid())
            {
                q.push(nxt);
                visited[nxt.y][nxt.x] = true;
            }
        }
    }
    cout << (ans ? to_string(ans) : "TT") << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}