#include <iostream>
#include <cstring>

using namespace std;

struct Point
{
    int y, x;
    void operator+=(Point other)
    {
        y += other.y;
        x += other.x;
    }
    int mask() const;
};
constexpr Point DIR[5] = {{0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int m, a, ans;
int moves[2][101];
int map_[11][11];
int power[8];
Point user[2];

inline int Point::mask() const
{
    return map_[y][x];
}

void setBC(Point bc, int c, int mask)
{
    for (int i = 1; i <= 10; ++i)
        for (int j = 1; j <= 10; ++j)
            if (abs(i - bc.y) + abs(j - bc.x) <= c)
                map_[i][j] |= mask;
}

int maxCharge(int maskA, int maskB)
{
    int ret = 0;
    for (int iA = 0; iA < a; ++iA)
    {
        int pA = (maskA & (1 << iA)) ? power[iA] : 0;
        for (int iB = 0; iB < a; ++iB)
        {
            int pB = (maskB & (1 << iB)) ? power[iB] : 0;
            if (iA == iB && pA && pB)
                ret = max(ret, pA);
            else
                ret = max(ret, pA + pB);
        }
    }
    return ret;
}

void init()
{
    memset(map_, 0, sizeof(map_));
    ans = 0;
    user[0] = {1, 1};
    user[1] = {10, 10};
}

void input()
{
    cin >> m >> a;
    for (int i = 0; i < 2; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> moves[i][j];
    for (int i = 0; i < a; ++i)
    {
        int y, x, c;
        cin >> x >> y >> c >> power[i];
        setBC({y, x}, c, 1 << i);
    }
}

void solve()
{
    for (int j = 0; j <= m; ++j)
    {
        for (int i = 0; i < 2; ++i)
            user[i] += DIR[moves[i][j]];
        ans += maxCharge(user[0].mask(), user[1].mask());
    }
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