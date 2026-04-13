#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int n, m, ans;
string map_[600];

struct Point
{
    int y, x;
    Point operator+(Point other) const
    {
        return {y + other.y, x + other.x};
    }
    bool isValid() const
    {
        return 0 <= y && y < n && 0 <= x && x < m && map_[y][x] != 'X';
    }
};

const Point DIR[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int dfs(Point cur)
{
    int ret = map_[cur.y][cur.x] == 'P';
    map_[cur.y][cur.x] = 'X';
    for (Point d : DIR)
    {
        Point nxt = cur + d;
        if (nxt.isValid())
            ret += dfs(nxt);
    }
    return ret;
}

void solve()
{
    cin >> n >> m;
    Point start;
    for (int i = 0; i < n; ++i)
    {
        cin >> map_[i];
        size_t j = map_[i].find('I');
        if (j != string::npos)
            start.y = i, start.x = j;
    }
    int ans = dfs(start);
    cout << (ans ? to_string(ans) : "TT") << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}