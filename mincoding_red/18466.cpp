#include <cmath>
#include <iostream>
using namespace std;

int ret;
int n;
int metro[21];

void init()
{
    ret = 0;
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> metro[i];
    }
}

void check(int a, int b, int c, int d)
{
    if (a == 0 && d == n - 1)
        return;
    a = metro[a], b = metro[b], c = metro[c], d = metro[d];
    ret = max(ret, (a + b) * (a + b) + (c + d) * (c + d));
    ret = max(ret, (a + d) * (a + d) + (b + c) * (b + c));
}

void solve()
{
    for (int a = 0; a < n; ++a)
    {
        for (int b = a + 2; b < n; ++b)
        {
            for (int c = b + 2; c < n; ++c)
            {
                for (int d = c + 2; d < n; ++d)
                {
                    check(a, b, c, d);
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}