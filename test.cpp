#include <iostream>

using namespace std;

int n, t, p;
int sizes[6];

void solve()
{
    cin >> n;
    for (int i = 0; i < 6; ++i)
        cin >> sizes[i];
    cin >> t >> p;
    int ans1 = 0, ans2 = 0, ans3 = 0;
    for (int i = 0; i < 6; ++i)
        ans1 += (sizes[i] + t - 1) / t;
    ans2 = n / p;
    ans3 = n % p;
    cout << ans1 << endl
         << ans2 << ' ' << ans3 << endl;
}

int main()
{
    // 빠른 입출력
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}