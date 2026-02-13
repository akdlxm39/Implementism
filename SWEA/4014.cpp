#include <cstring>
#include <iostream>
using namespace std;

int n, x, ret;
int map_[22][22];

void input()
{
    memset(map_, 0, sizeof(map_));
    ret = 0;
    cin >> n >> x;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> map_[i][j];
        }
    }
}

void solve()
{
    for (int i = 0; i < n; ++i)
    {
        int cur = map_[i][0], cur_len = 1;
        for (int j = 1; j < n; ++j)
        {
            if (map_[i][j] == cur)
            {
                cur_len++;
            }
            else if (map_[i][j] == cur + 1 && cur_len >= x)
            {
                cur = map_[i][j];
                cur_len = 1;
            }
            else if (map_[i][j] == cur - 1 && cur_len >= 0)
            {
                cur = map_[i][j];
                cur_len = -x + 1;
            }
            else
            {
                cur_len = -1;
                break;
            }
        }
        if (cur_len >= 0)
        {
            ret++;
        }
    }
    for (int j = 0; j < n; ++j)
    {
        int cur = map_[0][j], cur_len = 1;
        for (int i = 1; i < n; ++i)
        {
            if (map_[i][j] == cur)
            {
                cur_len++;
            }
            else if (map_[i][j] == cur + 1 && cur_len >= x)
            {
                cur = map_[i][j];
                cur_len = 1;
            }
            else if (map_[i][j] == cur - 1 && cur_len >= 0)
            {
                cur = map_[i][j];
                cur_len = -x + 1;
            }
            else
            {
                cur_len = -1;
                break;
            }
        }
        if (cur_len >= 0)
        {
            ret++;
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