#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

struct Customer
{
    int id;
    int time;
    int a;
    int b;
};

int ret;
int n, m, k, a, b;
int time1[10], time2[10];
int who1[10], who2[10];
Customer customers[1001];

void input()
{
    memset(who1, -1, sizeof(who1));
    memset(who2, -1, sizeof(who2));
    ret = 0;
    cin >> n >> m >> k >> a >> b;
    for (int i = 0; i < n; ++i)
        cin >> time1[i];
    for (int i = 0; i < m; ++i)
        cin >> time2[i];
    for (int i = 0; i < k; ++i)
    {
        customers[i].id = i + 1;
        cin >> customers[i].time;
    }
}

void solve()
{
    queue<int> q;
    int cur_time = 0;
    int idx = 0;
    int cnt = 0;
    int cnt1 = 0, cnt2 = 0;

    while (cnt < k)
    {
        for (int i = 0; i < n; ++i)
        {
            if (who1[i] != -1 && customers[who1[i]].time <= cur_time)
            {
                q.push(who1[i]);
                who1[i] = -1;
            }
            if (who1[i] == -1 && idx < k && customers[idx].time <= cur_time)
            {
                who1[i] = idx;
                customers[idx].time = cur_time + time1[i];
                customers[idx].a = i + 1;
                idx++;
            }
        }
        for (int i = 0; i < m; ++i)
        {
            if (who2[i] != -1 && customers[who2[i]].time <= cur_time)
            {
                who2[i] = -1;
                cnt++;
            }
            if (who2[i] == -1 && !q.empty())
            {
                who2[i] = q.front();
                customers[q.front()].time = cur_time + time2[i];
                customers[q.front()].b = i + 1;
                q.pop();
            }
        }
        cur_time++;
    }
    for (int i = 0; i < k; ++i)
    {
        if (customers[i].a == a && customers[i].b == b)
        {
            ret += customers[i].id;
        }
    }
    if (ret == 0)
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
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}