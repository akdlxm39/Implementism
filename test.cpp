#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

// [2] 이게 필요없었네
// 그냥 1이었던거를 현재 번호로 업데이트하고 0인지 아닌지만 확인하면 됨
int board[10][10][2];
int par[10];

int find(int x)
{
    if (par[x] < 0)
    {
        return x;
    }
    return par[x] = find(par[x]);
}

bool uni(int u, int v)
{
    u = find(u);
    v = find(v);

    if (u == v)
        return false;

    if (par[v] < par[u])
        swap(u, v);
    else if (par[u] == par[v])
        par[u]--;
    par[v] = u;

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    fill(par, par + 10, -1);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j][0];
        }
    }

    int ic_idx = 1;

    // BFS, 부품 카운트 및 분류
    vector<vector<bool>> visit(n, vector<bool>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visit[i][j])
                continue;
            if (board[i][j][0] == 0)
                continue;
            queue<pair<int, int>> q;
            q.push({i, j});
            visit[i][j] = 1;

            while (!q.empty())
            {
                auto cur = q.front();
                int cy = cur.first;
                int cx = cur.second;
                q.pop();
                board[cy][cx][1] = ic_idx;

                for (int dir = 0; dir < 4; dir++)
                {
                    int ny = cy + dy[dir];
                    int nx = cx + dx[dir];

                    if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                        continue;
                    if (visit[ny][nx])
                        continue;
                    if (board[ny][nx][0] == 0)
                        continue;

                    visit[ny][nx] = 1;
                    q.push({ny, nx});
                }
            }
            ic_idx++;
        }
    }

    // 가능한 모든 연결 구하기(중복 포함)
    vector<tuple<int, int, int>> edge;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j][0] == 0)
                continue;

            for (int dir = 0; dir < 4; dir++)
            {
                int ny = i;
                int nx = j;
                for (int k = 0; k <= 10; k++)
                {
                    ny += dy[dir];
                    nx += dx[dir];

                    if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                        break;
                    if (board[ny][nx][0] == 1)
                    {
                        if (board[i][j][1] == board[ny][nx][1])
                            break;
                        if (k < 2)
                            break;
                        edge.push_back({k, board[i][j][1], board[ny][nx][1]});
                    }
                }
            }
        }
    }

    // 최소길이니깐 오름차순으로 정리
    sort(edge.begin(), edge.end());

    // 간선 개수 = 노드 - 1
    int min_len = 0;
    int e_cnt = 1;
    for (int i = 0; i < edge.size(); i++)
    {
        int len, u, v;
        tie(len, u, v) = edge[i];
        if (uni(u, v))
        {
            min_len += len;
            e_cnt++;
        }
        if (e_cnt == ic_idx - 1)
            break;
    }

    if (e_cnt == ic_idx - 1)
        cout << min_len << '\n';
    else
        cout << -1 << '\n';

    return 0;
}