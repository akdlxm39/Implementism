#include <array>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int ret;
int n;
int work_time[51];
int cur_work_time[51];
int indegree[51];
int cur_indegree[51];
vector<int> next_works[51];

void input()
{
    ret = 987654321;
    cin >> n;
    for (int i = 0; i < 51; ++i)
        next_works[i].clear();
    for (int i = 1; i <= n; ++i)
    {
        cin >> work_time[i] >> indegree[i];
        for (int j = 0, p; j < indegree[i]; ++j)
        {
            cin >> p;
            next_works[p].push_back(i);
        }
    }
}

int topology(int chance)
{
    int total_time = 0;
    memset(cur_work_time, 0, sizeof(cur_work_time));
    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
            cur_work_time[i] = (i == chance ? work_time[i] / 2 : work_time[i]);
        }
        cur_indegree[i] = indegree[i];
    }
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        if (total_time < cur_work_time[cur])
            total_time = cur_work_time[cur];
        for (int i = 0; i < next_works[cur].size(); ++i)
        {
            int nxt = next_works[cur][i];
            int nxt_work_time = cur_work_time[cur];
            nxt_work_time += (nxt == chance ? work_time[nxt] / 2 : work_time[nxt]);
            if (cur_work_time[nxt] < nxt_work_time)
                cur_work_time[nxt] = nxt_work_time;
            if (--cur_indegree[nxt] == 0)
                q.push(nxt);
        }
    }
    return total_time;
}

bool check()
{
    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
        cur_indegree[i] = indegree[i];
    }
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < next_works[cur].size(); ++i)
        {
            int nxt = next_works[cur][i];
            if (--cur_indegree[nxt] == 0)
            {
                q.push(nxt);
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (cur_indegree[i])
            return false;
    }
    return true;
}

void solve()
{
    if (!check())
    {
        ret = -1;
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        int tmp = topology(i);
        if (ret > tmp)
            ret = tmp;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}