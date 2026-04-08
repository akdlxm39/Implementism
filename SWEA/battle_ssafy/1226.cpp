#include <iostream>
#include <string>

using namespace std;

struct Point
{
    int y, x;
    Point operator+(Point other) const;
    bool isValid() const;
};

const int SIZE = 16;
const Point DIR[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

string map_[SIZE];
Point start;
int ans;

inline Point Point::operator+(Point other) const
{
    return {y + other.y, x + other.x};
}

inline bool Point::isValid() const
{
    return 0 <= y && y < SIZE && 0 <= x && x < SIZE && map_[y][x] != '1';
}

bool dfs(Point cur)
{
    map_[cur.y][cur.x] = '1';
    for (Point d : DIR)
    {
        Point nxt = cur + d;
        if (nxt.isValid() && (map_[nxt.y][nxt.x] == '3' || dfs(nxt)))
            return true;
    }
    return false;
}

void init()
{
}

void input()
{
    int dummy;
    cin >> dummy;
    for (int i = 0; i < SIZE; ++i)
    {
        cin >> map_[i];
        size_t j = map_[i].find('2');
        if (j != string::npos)
            start.y = i, start.x = j;
    }
}

void solve()
{
    ans = dfs(start);
}

void output(int testCase)
{
    cout << '#' << testCase << ' ' << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 10;
    for (int testCase = 1; testCase <= T; ++testCase)
    {
        init();
        input();
        solve();
        output(testCase);
    }

    return 0;
}