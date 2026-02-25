#include <iostream>
#include <vector>

using namespace std;

const int MAX_SIZE = 40001;

struct Edge
{
    int to, cost;
};

struct Query
{
    int target, idx;
};

int n, m;

// 인접 리스트 {to, cost}
vector<Edge> adj_list[MAX_SIZE];
// 쿼리 리스트 {target, idx}
vector<Query> queries[MAX_SIZE];

// 상태 및 정보 배열
bool visited[MAX_SIZE];
int parent[MAX_SIZE], _rank[MAX_SIZE];
int ancestor[MAX_SIZE];
int dist_arr[MAX_SIZE]; // 루트로부터의 누적 거리 저장

// 정답 배열 (쿼리 최대 10,000개)
int answers[10001];

// union by rank: find
int _find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = _find(parent[x]);
}

// union by rank
void _union(int u, int v)
{
    u = _find(u);
    v = _find(v);
    if (u == v)
        return;
    if (_rank[u] < _rank[v])
    {
        parent[u] = v;
    }
    else
    {
        parent[v] = u;
        if (_rank[u] == _rank[v])
            _rank[u]++;
    }
}

// Tarjan's Offline LCA + 거리 계산
void LCA(int cur, int current_dist)
{
    ancestor[cur] = cur;
    visited[cur] = true;
    dist_arr[cur] = current_dist; // 루트부터 현재 노드까지의 누적 거리 기록

    for (auto edge : adj_list[cur])
    {
        int nxt = edge.to;
        int cost = edge.cost;

        if (!visited[nxt])
        {
            LCA(nxt, current_dist + cost); // 다음 노드로 이동하며 거리 누적
            _union(cur, nxt);
            ancestor[_find(cur)] = cur;
        }
    }

    for (Query q : queries[cur])
    {
        int target = q.target;
        if (visited[target])
        {
            int lca_node = ancestor[_find(target)];
            // [거리 공식] = 내 누적 거리 + 타겟 누적 거리 - (공통 조상 누적 거리 * 2)
            answers[q.idx] = dist_arr[cur] + dist_arr[target] - 2 * dist_arr[lca_node];
        }
    }
}

void solve()
{
    cin >> n;

    // 부모를 자기 자신으로 초기화
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
    }

    int u, v, c;
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> u >> v >> c;
        adj_list[u].push_back({v, c});
        adj_list[v].push_back({u, c});
    }

    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        queries[u].push_back({v, i});
        queries[v].push_back({u, i});
    }

    // 1번 노드를 루트로 삼고 탐색 시작 (초기 누적 거리 0)
    LCA(1, 0);

    for (int i = 0; i < m; ++i)
    {
        cout << answers[i] << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}