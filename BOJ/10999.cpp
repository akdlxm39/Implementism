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
        bucket[bNum] += lazy[bNum] * (endIdx - startIdx + 1);
        lazy[bNum] = 0;
    }
}

void update(int left, int right, ll delta)
{
    if (left % bucketSize)
    {
        int bNum = left / bucketSize;
        int idx = bucketSize * bNum;
        for (idx; idx < left; ++idx)
            arr[idx] += lazy[bNum];
        for (idx; idx < (bNum + 1) * bucketSize; ++idx)
            arr[idx] += lazy[bNum] + delta;
        bucket[bNum] += bucketSize * lazy[bNum];
        lazy[bNum] = 0;
    }
    for (int idx = (left - 1) / bucketSize + 1; idx < (right + 1) / bucketSize; ++idx)
    {
        lazy[idx] += delta;
    }
    if ((right + 1) % bucketSize)
    {
        int bNum = right / bucketSize;
        int idx = bucketSize * bNum;
        for (idx; idx <= right; ++idx)
            arr[idx] += lazy[bNum] + delta;
        for (idx; idx < min(n, (bNum + 1) * bucketSize); ++idx)
            arr[idx] += lazy[bNum];
        bucket[bNum] += bucketSize * lazy[bNum];
        lazy[bNum] = 0;
    }
}

ll query(int left, int right)
{
    ll ret = 0;
    if (left % bucketSize)
    {
        int bNum = left / bucketSize;
        int idx = bucketSize * bNum;
        for (idx; idx < left; ++idx)
            arr[idx] += lazy[bNum];
        for (idx; idx < (bNum + 1) * bucketSize; ++idx)
            ret += arr[idx] += lazy[bNum];
        bucket[bNum] += bucketSize * lazy[bNum];
        lazy[bNum] = 0;
    }
    for (int idx = (left - 1) / bucketSize + 1; idx < (right + 1) / bucketSize; ++idx)
    {
        ret += bucket[idx] + lazy[idx];
    }
    if ((right + 1) % bucketSize)
    {
        int bNum = right / bucketSize;
        int idx = bucketSize * bNum;
        for (idx; idx <= right; ++idx)
            ret += arr[idx] += lazy[bNum];
        for (idx; idx < min(n, (bNum + 1) * bucketSize); ++idx)
            arr[idx] += lazy[bNum];
        bucket[bNum] += bucketSize * lazy[bNum];
        lazy[bNum] = 0;
    }
    return ret;
}

void solve()
{
    cin >> n >> m >> k;
    bucketSize = sqrt(n);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}