#include <cstring>
#include <iostream>

using namespace std;

int ret = 987654321;
int n;
int synergy[16][16];
int A[8], B[8];

void input()
{
    ret = 987654321;
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> synergy[i][j];
}

void calc()
{
    int gap = 0;
    for (int i = 0; i < n / 2; ++i)
    {
        for (int j = 0; j < n / 2; ++j)
        {
            gap += synergy[A[i]][A[j]];
            gap -= synergy[B[i]][B[j]];
        }
    }
    if (gap < 0)
        gap = -gap;
    if (ret > gap)
        ret = gap;
}

void func(int cur, int ai, int bi)
{
    if (cur == n)
    {
        calc();
        return;
    }
    if (ai < n / 2)
    {
        A[ai] = cur;
        func(cur + 1, ai + 1, bi);
        A[ai] = -1;
    }
    if (bi < n / 2)
    {
        B[bi] = cur;
        func(cur + 1, ai, bi + 1);
        B[bi] = -1;
    }
}

void solve()
{
    func(0, 0, 0);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}