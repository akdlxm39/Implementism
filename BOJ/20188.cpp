#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define ll long long

int n;
vector<int> adj_list[300'007];
vector<int> cur_v;
int depth[300'007];
int node_cnt[300'007];
ll child_to_me[300'007];
ll child_to_child[300'007];
ll me_to_top[300'007];
ll ans;

void input()
{
    memset(depth, -1, sizeof(depth));
    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
}

void bfs()
{
    queue<int> q;
    q.push(1);
    depth[1] = 0;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        cur_v.push_back(cur);
        for (int nxt : adj_list[cur])
        {
            if (depth[nxt] != -1)
                continue;
            depth[nxt] = depth[cur] + 1;
            q.push(nxt);
        }
    }
}

void solve()
{
    bfs();
    while (!cur_v.empty())
    {
        int cur = cur_v.back();
        cur_v.pop_back();

        for (int i = 0; i < adj_list[cur].size(); ++i)
        {
            int child = adj_list[cur][i];
            if (depth[cur] > depth[child])
                continue;
            node_cnt[cur] += node_cnt[child];
            child_to_me[cur] += child_to_me[child] + node_cnt[child];
            me_to_top[cur] += depth[cur] * node_cnt[child];
        }
        int tmp_cnt = node_cnt[cur];
        for (int i = 0; i < adj_list[cur].size(); ++i)
        {
            int child = adj_list[cur][i];
            if (depth[cur] > depth[child])
                continue;
            child_to_child[cur] += (child_to_me[child] + node_cnt[child]) * (node_cnt[cur] - node_cnt[child]);
            tmp_cnt -= node_cnt[child];
            me_to_top[cur] += depth[cur] * node_cnt[child] * tmp_cnt;
        }
        ans += child_to_child[cur] + child_to_me[cur] + me_to_top[cur];
        node_cnt[cur]++;
    }

    cout << ans << '\n';
}
void test_input()
{

    memset(depth, -1, sizeof(depth));
    n = 4;
    for (int i = 1; i < n; ++i)
    {
        adj_list[i].push_back(i + 1);
        adj_list[i + 1].push_back(i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    test_input();
    // input();
    solve();

    return 0;
}