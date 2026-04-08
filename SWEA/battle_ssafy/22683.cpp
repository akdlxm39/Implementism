#include <iostream>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

struct Point
{
    int y, x;
    Point operator+(Point other) const;
    bool isValid() const;
};

struct Info
{
    Point pos;
    int opCnt, restCutCnt;
};

const int MAX_SIZE = 10;
const Point DIR[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int n, k;
string map_[MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
Point start;

inline Point Point::operator+(Point other) const
{
    return {y + other.y, x + other.x};
}

inline bool Point::isValid() const
{
    return 0 <= y && y < n && 0 <= x && x < n;
}

void init()
{
    memset(visited, -1, sizeof(visited));
}

void input()
{
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        cin >> map_[i];
        size_t j = map_[i].find('X');
        if (j != string::npos)
            start.y = i, start.x = j;
    }
}

int bfs(Point start)
{
    queue<Info> q;
    q.emplace(start, 0, k);
    visited[start.y][start.x] = k;
    while (!q.empty())
    {
        Info cur = q.front();
        q.pop();
    }
}

void solve()
{
}

void output(int testCase)
{
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
        input() : solve();
        output(testCase);
    }

    return 0;
}