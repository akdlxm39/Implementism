#include <iostream>
using namespace std;

int ret;
int n, l;
int taste[21], kcal[21], taste_sum;

void input()
{
    ret = 0;
    taste_sum = 0;
    cin >> n >> l;
    for (int i = 0; i < n; ++i)
    {
        cin >> taste[i] >> kcal[i];
        taste_sum += taste[i];
    }
}

void backtracking(int cur, int total_taste, int total_kcal, int rest_taste)
{
    if (total_kcal > l || total_taste + rest_taste < ret)
        return;
    if (cur == n)
    {
        if (ret < total_taste)
            ret = total_taste;
        return;
    }
    backtracking(cur + 1, total_taste + taste[cur], total_kcal + kcal[cur], rest_taste - taste[cur]);
    backtracking(cur + 1, total_taste, total_kcal, rest_taste - taste[cur]);
}

void solve()
{
    backtracking(0, 0, 0, taste_sum);
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