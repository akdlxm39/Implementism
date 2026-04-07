#include <iostream>

using namespace std;

int g, p;
int pre[100'001];

int find(int x)
{
    if (pre[x] == x)
        return x;
    return pre[x] = find(pre[x]);
}

bool dock(int x)
{
    int docker = find(x);
    if (docker == 0)
        return false;
    pre[docker] = find(docker - 1);
    return true;
}

void solve()
{
    cin >> g >> p;
    for (int i = 1; i <= g; ++i)
        pre[i] = i;
    int ans, x;
    for (ans = 0; ans < p; ++ans)
    {
        cin >> x;
        if (!dock(x))
            break;
    }
    cout << ans << '\n';
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}