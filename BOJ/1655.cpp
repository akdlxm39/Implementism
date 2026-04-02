#include <iostream>

using namespace std;

int n;

int tree[20002];

void update(int idx)
{
    while (idx <= 20001)
    {
        tree[idx]++;
        idx += idx & -idx;
    }
}

int query(int kth)
{
    int idx = 0;
    for (int step = 16384; step > 0; step >>= 1)
    {
        int nxt = idx + step;
        if (nxt <= 20001 && tree[nxt] < kth)
        {
            kth -= tree[nxt];
            idx = nxt;
        }
    }
    return idx + 1;
}

void solve()
{
    cin >> n;
    int x;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        update(x + 10001);
        cout << query(i / 2 + 1) - 10001 << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}