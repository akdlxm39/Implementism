#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> adj_list[1'000'001];

int dfs(int cur, int prev, int check)
{
    //
    int ret = 0;
    if (check)
    {
        ret++;
        for (int nxt : adj_list[cur])
        {
            if (nxt == prev)
                continue;
            ret += min(dfs(nxt, cur, true), dfs(nxt, cur, false));
        }
    }
    else
    {
        for (int nxt : adj_list[cur])
        {
            if (nxt == prev)
                continue;
            ret += dfs(nxt, cur, true);
        }
    }
    return ret;
}

int main()
{
    // 입력
    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    // 출력
    // 루트 노드가 얼리어답터일 때, 아닐 때를 비교
    cout << min(dfs(1, 0, true), dfs(1, 0, false)) << '\n';

    return 0;
}