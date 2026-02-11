#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int ret;
int n, total_voters;
int adj_matrix[9][9];
int voter[9];
bool a_group[9];
bool visited[9];

void init()
{
    ret = 21e8;
    total_voters = 0;
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> adj_matrix[i][j];
    for (int i = 0; i < n; ++i)
    {
        cin >> voter[i];
        total_voters += voter[i];
    }
}

int bfs(int i)
{
    // 각 지역구의 마을들이 이어져 있다면, cnt == 지역구 마을 수
    int cnt = 1;
    queue<int> q;
    q.push(i);
    visited[i] = true;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int nxt = 0; nxt < n; ++nxt)
        {
            if (visited[nxt] || !adj_matrix[cur][nxt] || a_group[nxt] != a_group[cur])
                continue;
            cnt++;
            q.push(nxt);
            visited[nxt] = true;
        }
    }
    return cnt;
}

bool check(int a_cnt)
{
    // visited 초기화를 여기서 하는 이유 :
    //  visited는 check마다 두 번의 bfs에서 사용, 같은 마을에 접근할 가능성은 없음 (지역구가 다르기 때문)
    memset(visited, false, sizeof(visited));
    // A지역구에 속한 첫번째 마을을 찾아서 bfs실행 -> a_cnt와 bfs의 리턴값이 같다면 통과
    // bfs를 한번만 해야 하므로, break 사용
    for (int i = 0; i < n; ++i)
    {
        if (a_group[i] == true)
        {
            if (bfs(i) != a_cnt)
                return false;
            break;
        }
    }
    // B지역구에 속한 첫번째 마을을 찾아서 bfs실행 -> n-a_cnt와 bfs의 리턴값이 같다면 통과
    // bfs를 한번만 해야 하므로, break 사용
    for (int i = 0; i < n; ++i)
    {
        if (a_group[i] == false)
        {
            if (bfs(i) != n - a_cnt)
                return false;
            break;
        }
    }
    return true;
}

void dfs(int cur, int a_cnt, int a_voters)
{
    // 종료조건 : 모든 마을이 각 지역구에 배정되었을 때
    if (cur == n)
    {
        // 성공조건 : 각 지역구의 마을들이 이어져 있다면
        if (check(a_cnt))
            // 두 지역구 유권자 수 차이 : a_voters - (total_voters - a_voters)
            ret = min(ret, abs(a_voters * 2 - total_voters));
        return;
    }

    // cur 마을을 A지역구에 배정
    a_group[cur] = true;
    dfs(cur + 1, a_cnt + 1, a_voters + voter[cur]);
    // cur 마을을 A지역구에 미배정 (== B지역구에 배정)
    a_group[cur] = false;
    dfs(cur + 1, a_cnt, a_voters);
}

void solve()
{
    dfs(0, 0, 0);
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