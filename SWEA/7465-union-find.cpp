#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int ret;
int n, m;
vector<int> parent;

int _find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = _find(parent[x]);
}

bool _union(int a, int b)
{
    a = _find(a);
    b = _find(b);
    if (a == b)
        return false;
    parent[a] = b;
    return true;
}

void solve()
{
    cin >> n >> m;
    ret = n;
    parent.clear();
    for (int i = 0; i <= n; ++i)
        parent.push_back(i);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        if (_union(u, v))
            ret--;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        solve();
        cout << '#' << tc << ' ' << ret << '\n';
    }

    return 0;
}