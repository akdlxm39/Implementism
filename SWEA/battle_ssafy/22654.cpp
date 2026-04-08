#include <iostream>

using namespace std;

struct Point
{
    int y, x;
    Point operator+(Point other) const;
    bool isValid() const;
};

const Point DIR[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int n, q, ans[5];
string map_[5], commands[5];
Point start;

inline Point Point::operator+(Point other) const
{
    return {y + other.y, x + other.x};
}

inline bool Point::isValid() const
{
    return 0 <= y && y < n && 0 <= x && x < n && map_[y][x] != 'T';
}

bool tryCommand(const string &command)
{
    Point cur = start, nxt;
    int curDir = 0;
    for (char c : command)
    {
        switch (c)
        {
        case 'A':
            nxt = cur + DIR[curDir];
            if (nxt.isValid())
                cur = nxt;
            break;
        case 'L':
            curDir = (curDir + 3) % 4;
            break;
        case 'R':
            curDir = (curDir + 1) % 4;
            break;
        }
    }
    return map_[cur.y][cur.x] == 'Y';
}

void init()
{
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> map_[i];
        size_t j = map_[i].find('X');
        if (j != string::npos)
            start.y = i, start.x = j;
    }
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int dummy;
        cin >> dummy >> commands[i];
    }
}

void solve()
{
    for (int i = 0; i < q; ++i)
        ans[i] = tryCommand(commands[i]);
}

void output(int testCase)
{
    cout << '#' << testCase << ' ';
    for (int i = 0; i < q; ++i)
        cout << ans[i] << ' ';
    cout << '\n';
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