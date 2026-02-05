#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, st, e, max_ans, min_ans;
int adj_matrix[10][10];
bool visited[10];

void input()
{
    min_ans = 21e8;
    max_ans = -21e8;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> adj_matrix[i][j];
        }
    }
    cin >> st >> e;
}

void dfs(int cur, int cost)
{
    if (cur == e)
    {
        max_ans = max(max_ans, cost);
        min_ans = min(min_ans, cost);
        return;
    }
    for (int nxt = 0; nxt < n; ++nxt)
    {
        if (visited[nxt] || adj_matrix[cur][nxt] == 0)
            continue;
        visited[nxt] = true;
        dfs(nxt, cost + adj_matrix[cur][nxt]);
        visited[nxt] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();

    visited[st] = true;
    dfs(st, 0);

    cout << min_ans << '\n' << max_ans << '\n';

    return 0;
}