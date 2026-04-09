#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

int n;
int level[300'001];

void solve()
{
    cin >> n;
    if (n == 0)
    {
        cout << 0 << '\n';
        return;
    }
    for (int i = 0; i < n; ++i)
        cin >> level[i];
    sort(level, level + n);
    int x = round(double(n) * 0.15);
    double mean = accumulate(level + x, level + n - x, 0.0) / (n - 2 * x);
    cout << round(mean) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}