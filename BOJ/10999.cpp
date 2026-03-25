#include <iostream>
#include <cmath>
#define ll long long
using namespace std;

int n, m, k;
int bucketSize;
ll arr[1'000'001];
ll bucket[1'001];
ll lazy[1'001];

void lazy_update(int bNum)
{
    if (lazy[bNum])
    {
        int startIdx = bNum * bucketSize;
        int endIdx = min(n, startIdx + bucketSize);
        for (int i = startIdx; i < endIdx; ++i)
            arr[i] += lazy[bNum];
        bucket[bNum] += lazy[bNum] * (endIdx - startIdx);
        lazy[bNum] = 0;
    }
}

void update(int left, int right, ll delta)
{
    int bLeft = left / bucketSize;
    int bRight = right / bucketSize;

    if (bLeft == bRight)
    {
        lazy_update(bLeft);
        for (int i = left; i <= right; ++i)
            arr[i] += delta;
        bucket[bLeft] += delta * (right - left + 1);
        return;
    }
    lazy_update(bLeft);
    for (int i = left; i < (bLeft + 1) * bucketSize; ++i)
    {
        arr[i] += delta;
        bucket[bLeft] += delta;
    }
    for (int b = bLeft + 1; b < bRight; ++b)
        lazy[b] += delta;
    lazy_update(bRight);
    for (int i = bRight * bucketSize; i <= right; ++i)
    {
        arr[i] += delta;
        bucket[bRight] += delta;
    }
}

ll query(int left, int right)
{
    ll ret = 0;
    int bLeft = left / bucketSize;
    int bRight = right / bucketSize;
    if (bLeft == bRight)
    {
        lazy_update(bLeft);
        for (int i = left; i <= right; ++i)
            ret += arr[i];
        return ret;
    }
    lazy_update(bLeft);
    for (int i = left; i < (bLeft + 1) * bucketSize; ++i)
        ret += arr[i];
    for (int b = bLeft + 1; b < bRight; ++b)
        ret += bucket[b] + lazy[b] * bucketSize;
    lazy_update(bRight);
    for (int i = bRight * bucketSize; i <= right; ++i)
        ret += arr[i];
    return ret;
}

void solve()
{
    cin >> n >> m >> k;
    bucketSize = sqrt(n);
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
        bucket[i / bucketSize] += arr[i];
    }
    int a, b, c;
    ll d;
    for (int i = 0; i < m + k; ++i)
    {
        cin >> a;
        if (a == 1)
        {
            cin >> b >> c >> d;
            update(b, c, d);
        }
        else if (a == 2)
        {
            cin >> b >> c;
            cout << query(b, c) << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}