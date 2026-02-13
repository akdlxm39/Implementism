#include <algorithm>
#include <iostream>
using namespace std;

long long n, ans_total, ans_money;
int pay_for[1000001];

void input()
{
    cin >> n;
    for (int i = 0, x; i < n; ++i)
    {
        cin >> x;
        pay_for[x]++;
    }
}

void solve()
{
    int cnt = 0;
    for (int money = 1'000'000; money >= 1; --money)
    {
        if (pay_for[money] == 0)
            continue;
        cnt += pay_for[money];
        long long cur_total = (long long)cnt * money;
        if (ans_total <= cur_total)
        {
            ans_total = cur_total;
            ans_money = money;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        input();
        solve();
        cout << ans_total << ' ' << ans_money << '\n';
    }
}