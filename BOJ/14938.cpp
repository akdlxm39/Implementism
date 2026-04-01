#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

int n, m, r;
int items[101];
int dists[101][101];

void solve()
{
    cin >> n >> m >> r;
    for (int i = 1; i <= n; ++i)
    {
        cin >> items[i];
        for (int j = 1; j <= n; ++j)
            dists[i][j] = INF;
        dists[i][i] = 0;
    }
    int u, v, c;
    for (int i = 0; i < r; ++i)
    {
        cin >> u >> v >> c;
        dists[u][v] = dists[v][u] = c;
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (dists[i][j] > dists[i][k] + dists[k][j])
                    dists[i][j] = dists[i][k] + dists[k][j];
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int tmp = 0;
        for (int j = 1; j <= n; ++j)
            if (dists[i][j] <= m)
                tmp += items[j];
        if (ans < tmp)
            ans = tmp;
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}