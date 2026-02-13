#include <algorithm>
#include <iostream>
using namespace std;

int ret;
int n;
int want[501];
int hat[501];

void init()
{
    ret = 0;
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> want[i];
    for (int i = 0; i < n; ++i)
        cin >> hat[i];
}

void solve()
{
    sort(want, want + n);
    sort(hat, hat + n);
    int i = 0, j = 0;
    while (i < n && j < n)
    {
        if (want[i] + 3 < hat[j])
        {
            i++;
        }
        else if (hat[j] < want[i] - 3)
        {
            j++;
        }
        else
        {
            ret++;
            i++;
            j++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}