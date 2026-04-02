#include <iostream>

using namespace std;

int n;
int nums[101];
long long dp[101][21];

void solve()
{
    cin >> n;
    for (int i = 0, x; i < n; ++i)
        cin >> nums[i];
    dp[0][nums[0]] = 1LL;
    for (int i = 0; i < n - 2; ++i)
    {
        for (int j = 0; j <= 20; ++j)
        {
            if (dp[i][j] == 0)
                continue;
            if (j + nums[i + 1] <= 20)
                dp[i + 1][j + nums[i + 1]] += dp[i][j];
            if (nums[i + 1] <= j)
                dp[i + 1][j - nums[i + 1]] += dp[i][j];
        }
    }
    cout << dp[n - 2][nums[n - 1]] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}