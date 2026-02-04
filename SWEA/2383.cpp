#include <iostream>
#include <vector>
using namespace std;

int ret;

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
    user_cnt = 0;
    stair_cnt = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int x;
            if (x == 1)
                users[user_cnt++] = {i, j};
            else if (x != 0)
                stairs[stair_cnt++] = {i, j, x};
        }
    }
}

void dfs(int cur)
{
}

void solve()
{
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