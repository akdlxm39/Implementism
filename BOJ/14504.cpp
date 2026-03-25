#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 100'005;
const int B_SIZE = 512;
const int B_SHIFT = 9;
const int MAX_B = (MAX_N >> 9) + 2;

int n, m;
int arr[MAX_N];
int bucket[MAX_B][B_SIZE];

void update(int idx, int num)
{
    int bIdx = idx >> B_SHIFT;
    int *iter = lower_bound(bucket[bIdx], bucket[bIdx + 1], arr[idx]);
    if (num > arr[idx])
    {
        int *pos = upper_bound(iter, bucket[bIdx + 1], num) - 1;
        copy(iter + 1, pos + 1, iter);
        *pos = num;
    }
    else if (num < arr[idx])
    {
        int *pos = lower_bound(bucket[bIdx], iter, num);
        copy_backward(pos, iter, iter + 1);
        *pos = num;
    }
    arr[idx] = num;
}

int query(int left, int right, int num)
{
    int ret = 0;
    int bLeft = left >> B_SHIFT;
    int bRight = right >> B_SHIFT;
    if (bLeft == bRight)
    {
        for (int i = left; i <= right; ++i)
            ret += (arr[i] > num);
        return ret;
    }
    for (int i = left; i < ((bLeft + 1) << B_SHIFT); ++i)
        ret += (arr[i] > num);
    for (int b = bLeft + 1; b < bRight; ++b)
        ret += distance(upper_bound(bucket[b], bucket[b + 1], num), bucket[b + 1]);
    for (int i = bRight << B_SHIFT; i <= right; ++i)
        ret += (arr[i] > num);
    return ret;
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        bucket[i >> B_SHIFT][i & (B_SIZE - 1)] = arr[i];
    }
    for (int b = 0; b <= n >> B_SHIFT; ++b)
        sort(bucket[b], bucket[b + 1]);
    cin >> m;
    int q, a, b, c;
    for (int i = 0; i < m; ++i)
    {
        cin >> q;
        if (q == 1)
        {
            cin >> a >> b >> c;
            cout << query(a - 1, b - 1, c) << '\n';
        }
        else if (q == 2)
        {
            cin >> a >> b;
            update(a - 1, b);
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