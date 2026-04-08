#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, abs_sum, i1, i2, i3;
int nums[5001];

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> nums[i];
    sort(nums, nums + n);
    abs_sum = 21e8;
    int l = 0, r = n - 1, m;
    while (l + 1 < r)
    {
        int tmp = nums[l] + nums[r];
        m = lower_bound(nums + l, nums + r, -tmp) - nums;
        if (m)
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}