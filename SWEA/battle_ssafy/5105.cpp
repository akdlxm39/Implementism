#include <iostream>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

int n, ans;
string map_[51];
int dist_[51][51];

struct Point
{
    int y, x;
    Point operator+(Point other) const
    {
        return {y + other.y, x + other.x};
    }
    bool isValid() const
    {
        return 0 <= y && y < n && 0 <= x && x < n && map() != '1' && dist() == -1;
    }
    char map() const
    {
        return map_[y][x];
    }
    int &dist() const
    {
        return dist_[y][x];
    }
} start;
constexpr Point DIR[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int bfs()
{
    queue<Point> q;
    q.push(start);
    start.dist() = 0;
    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();
        for (Point d : DIR)
        {
            Point nxt = cur + d;
            if (!nxt.isValid())
                continue;
            if (nxt.map() == '3')
                return cur.dist();
            nxt.dist() = cur.dist() + 1;
            q.push(nxt);
        }
    }
    return 0;
}

void init()
{
    memset(dist_, -1, sizeof(dist_));
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> map_[i];
        size_t j = map_[i].find('2');
        if (j != string::npos)
            start.y = i, start.x = j;
    }
}

void solve()
{
    ans = bfs();
}

void output(int testCase)
{
    cout << '#' << testCase << ' ' << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int testCase = 1; testCase <= T; ++testCase)
    {
        init();
        input();
        solve();
        output(testCase);
    }

    return 0;
}