

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

int ret, n, tallest_tree;
int trees[101], two, one;

void init()
{
    memset(trees, 0, sizeof(trees));
    ret = 0;
    n = 0;
    tallest_tree = 0;
    two = 0;
    one = 0;
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> trees[i];
        if (tallest_tree < trees[i])
        {
            tallest_tree = trees[i];
        }
    }
}

void solve()
{
    for (int i = 0; i < n; ++i)
    {
        two += (tallest_tree - trees[i]) / 2;
        one += (tallest_tree - trees[i]) % 2;
    }
    if (one > two)
    {
        ret = one * 2 - 1;
    }
    else
    {
        if ((two - one) % 3 == 2)
        {
            ret = (two - (two - one) / 3 - 1) * 2 + 1;
        }
        else
        {
            ret = (two - (two - one) / 3) * 2;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
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