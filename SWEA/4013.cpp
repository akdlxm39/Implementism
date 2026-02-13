#include <iostream>
using namespace std;

int k, ret;
int head[5];
int cogwheels[5][8];
int moves[20][2];

void input()
{
    ret = 0;
    cin >> k;
    for (int i = 1; i <= 4; ++i)
    {
        head[i] = 0;
        for (int j = 0; j < 8; ++j)
        {
            cin >> cogwheels[i][j];
        }
    }
    for (int i = 0; i < k; ++i)
    {
        cin >> moves[i][0] >> moves[i][1];
    }
}

void turn(int cur, int dir, int pre)
{
    if (cur > 1 && cur - 1 != pre && cogwheels[cur][(head[cur] + 6) % 8] != cogwheels[cur - 1][(head[cur - 1] + 2) % 8])
        turn(cur - 1, -dir, cur);
    if (cur < 4 && cur + 1 != pre && cogwheels[cur][(head[cur] + 2) % 8] != cogwheels[cur + 1][(head[cur + 1] + 6) % 8])
        turn(cur + 1, -dir, cur);
    head[cur] = (head[cur] + dir + 8) % 8;
}

void solve()
{
    for (int i = 0; i < k; ++i)
    {
        turn(moves[i][0], -moves[i][1], 10);
    }
    for (int i = 1; i <= 4; ++i)
    {
        if (cogwheels[i][head[i]])
        {
            ret += (1 << i - 1);
        }
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
        cout << '#' << tc << ' ' << ret << '\n';
    }
}