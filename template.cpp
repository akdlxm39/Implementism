#include <iostream>
using namespace std;

int ret;

void init()
{
}

void input()
{
}

void solve()
{
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