#include <algorithm>
#include <iostream>

using namespace std;

int n, ret;
int adj_matrix[13][13];
bool visited[13];

void input()
{
    ret = 987654321;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> adj_matrix[i][j];
        }
    }
}

void dfs(int cur, int cnt, int cost)
{
    if (cur == 0)
    {
        if (cnt == n)
        {
            ret = min(ret, cost);
            return;
        }
        if (cnt != 0)
            return;
    }
    for (int nxt = 0; nxt < n; ++nxt)
    {
        if (visited[nxt] || adj_matrix[cur][nxt] == 0)
            continue;
        visited[nxt] = true;
        dfs(nxt, cnt + 1, cost + adj_matrix[cur][nxt]);
        visited[nxt] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    dfs(0, 0, 0);

    cout << ret << '\n';

    return 0;
}