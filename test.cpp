#include <iostream>
#include <vector>
using namespace std;

int ret;
int n, cnt;
vector<int> v[101];
int degree[101];
bool visited[101];
bool checked[101];
bool is_cycle;

void init()
{
    ret = 0;
    cnt = 0;
    is_cycle = false;
    for (int i = 1; i <= n; ++i)
    {
        v[i].clear();
        visited[i] = false;
        checked[i] = false;
    }
}

void input()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> degree[i];
        for (int j = 0; i < degree[i]; ++j)
        {
            int x;
            cin >> x;
            v[x].push_back(i);
        }
    }
}

void dfs(int cur, int lev)
{
    if (ret < lev)
        ret = lev;
    if (!checked[cur])
    {
        checked[cur] = true;
        cnt++;
    }
    for (int i = 0; i < v[cur].size(); ++i)
    {
        if (visited[v[cur][i]])
        {
            is_cycle = true;
            return;
        }
        visited[v[cur][i]] = true;
        dfs(v[cur][i], lev + 1);
        visited[v[cur][i]] = false;
        if (is_cycle)
            return;
    }
}

void solve()
{
    for (int i = 1; i <= n; ++i)
    {
        if (degree[i] == 0)
        {
            visited[i] = true;
            dfs(i, 0);
            if (is_cycle)
                break;
        }
    }
    if (cnt != n || is_cycle)
        ret = -1;
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