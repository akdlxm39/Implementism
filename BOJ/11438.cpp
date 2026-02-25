#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 100'001;

struct Query
{
    int target, idx;
};

int n, m;
// 인접 리스트
vector<int> adj_list[MAX_SIZE];
// 쿼리 리스트 {target, idx}
vector<Query> queries[MAX_SIZE];
// visited
bool visited[MAX_SIZE];
// 부모, 랭크 (union by rank 사용 -> 더 이상 부모가 조상이 아님.)
int parent[MAX_SIZE], _rank[MAX_SIZE];
// 조상 (따로 조상 배열이 필요)
int ancestor[MAX_SIZE];
// 정답 배열 (오프라인 쿼리 사용)
int answers[100001];

// (union by rank) find
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

// Tarjan's Offline LCA
void LCA(int cur)
{
    ancestor[cur] = cur; // 첫 방문 시 내가 나의 조상이다.
    visited[cur] = true; // 방문 했다. (트리 구조 -> 재방문 막기 위해)
    for (int nxt : adj_list[cur])
    {
        if (!visited[nxt]) // 재방문 방지
        {
            LCA(nxt);         // 방문
            _union(cur, nxt); // 유니온
            // 유니온시 조상이 현재 노드의 부모가 바뀌었다면 그 부모의 조상을 현재 노드로 변경
            ancestor[_find(cur)] = cur;
        }
    }
    for (Query q : queries[cur])
    {
        int target = q.target;
        if (visited[target]) // 이미 방문한 노드라면 최소 공통 조상을 알 수 있음
        {
            answers[q.idx] = ancestor[_find(target)]; // 타겟노드의 부모의 조상이 최소공통조상
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
    int u, v;
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        queries[u].push_back({v, i});
        queries[v].push_back({u, i});
    }
    LCA(1);
    for (int i = 0; i < m; ++i)
    {
        cout << answers[i] << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    solve();

    return 0;
}