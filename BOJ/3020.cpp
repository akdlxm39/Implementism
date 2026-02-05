#include <iostream>
using namespace std;

int ret;
int n, h;
int breaks[500'002];
int min_cnt, min_break;
int cur_break;

void input()
{
    cin >> n >> h;
    min_break = n;
    for (int i = 0; i < n; ++i)
    {
        int height;
        cin >> height;
        if (i % 2)
            breaks[h - height + 1]++;
        else
            breaks[height + 1]--;
    }
}

void solve()
{
    int cur_break = n / 2;
    for (int i = 1; i <= h; ++i)
    {
        cur_break += breaks[i];
        if (min_break > cur_break)
        {
            min_break = cur_break;
            min_cnt = 1;
        }
        else if (min_break == cur_break)
            min_cnt++;
    }
    cout << min_break << ' ' << min_cnt << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}