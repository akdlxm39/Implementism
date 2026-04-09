#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Point
{
    int y, x;
    Point operator+(Point other) const;
    void operator+=(Point other);
    bool isValid() const;
    char &map() const;
};

const string TANK = "^v<>";
const Point DIR[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int height, width, n;
string map_[21], commands;
Point cur;
int curDir;

inline Point Point::operator+(Point other) const
{
    return {y + other.y, x + other.x};
}

inline void Point::operator+=(Point other)
{
    y += other.y;
    x += other.x;
}

inline bool Point::isValid() const
{
    return 0 <= y && y < height && 0 <= x && x < width;
}

inline char &Point::map() const
{
    return map_[y][x];
}

void move(int di)
{
    curDir = di;
    cur.map() = TANK[curDir];
    Point nxt = cur + DIR[curDir];
    if (nxt.isValid() && nxt.map() == '.')
    {
        swap(cur.map(), nxt.map());
        cur = nxt;
    }
}

void shoot()
{
    Point shell = cur + DIR[curDir];
    while (shell.isValid())
    {
        if (shell.map() == '*')
        {
            shell.map() = '.';
            break;
        }
        else if (shell.map() == '#')
        {
            break;
        }
        shell += DIR[curDir];
    }
}

void init()
{
}

void input()
{
    cin >> height >> width;
    for (int i = 0; i < height; ++i)
    {
        cin >> map_[i];
        size_t j = map_[i].find_first_of(TANK);
        if (j != string::npos)
        {
            cur.y = i, cur.x = j;
            curDir = TANK.find(map_[i][j]);
        }
    }
    cin >> n >> commands;
}

void solve()
{
    for (char command : commands)
    {
        switch (command)
        {
        case 'U':
            move(0);
            break;
        case 'D':
            move(1);
            break;
        case 'L':
            move(2);
            break;
        case 'R':
            move(3);
            break;
        case 'S':
            shoot();
            break;
        }
    }
}

void output(int testCase)
{
    cout << '#' << testCase << ' ';
    for (int i = 0; i < height; ++i)
        cout << map_[i] << '\n';
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