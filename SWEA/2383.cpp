#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int ans;

struct User
{
    int y;
    int x;
    int choice;
};

struct Stair
{
    int y;
    int x;
    int length;
};

int n, user_cnt, stair_cnt;
User users[11];
Stair stairs[2];

void input()
{
    ans = 987654321;
    user_cnt = 0;
    stair_cnt = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int x;
            cin >> x;
            if (x == 1)
                users[user_cnt++] = {i, j, 0};
            else if (x != 0)
                stairs[stair_cnt++] = {i, j, x};
        }
    }
}

void check()
{
    vector<int> v[2];
    for (int i = 0; i < user_cnt; ++i)
    {
        int cho = users[i].choice;
        int len = abs(users[i].y - stairs[cho].y) + abs(users[i].x - stairs[cho].x);
        v[cho].push_back(len);
    }

    int ret = 0;
    for (int i = 0; i < 2; ++i)
    {
        sort(v[i].begin(), v[i].end());
        queue<int> q;
        int time = 0, j = 0;
        for (; j < v[i].size(); ++time)
        {
            while (!q.empty() && q.front() <= time)
                q.pop();
            while (j < v[i].size() && v[i][j] <= time && q.size() < 3)
            {
                q.push(time + stairs[i].length);
                j++;
            }
        }
        for (; !q.empty(); ++time)
        {
            while (!q.empty() && q.front() <= time)
                q.pop();
        }
        ret = max(ret, time);
    }
    ans = min(ans, ret);
}

void dfs(int cur)
{
    if (cur == user_cnt)
    {
        check();
        return;
    }
    users[cur].choice = 0;
    dfs(cur + 1);
    users[cur].choice = 1;
    dfs(cur + 1);
}

void solve()
{
    dfs(0);
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
        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}