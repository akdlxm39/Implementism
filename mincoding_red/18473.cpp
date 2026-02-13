#include <cstring>
#include <iostream>
using namespace std;

constexpr int dy[4] = {1, 0, -1, 0}, dx[4] = {0, 1, 0, -1};

struct Command
{
    int r, c, s;
};

int ret;
int n, m, k;
int arr[51][51], tmp[51][51];
Command cmd[6];
int idx[6];
bool used[6];

void init()
{
    ret = 21e8;
}

void input()
{
    cin >> n >> m >> k;
    for (int y = 0; y < n; ++y)
        for (int x = 0; x < m; ++x)
            cin >> arr[y][x];
    for (int i = 0; i < k; ++i)
        cin >> cmd[i].r >> cmd[i].c >> cmd[i].s;
}

void turn(int y, int x, int sz)
{
    int tmp_num = tmp[y][x];
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < sz; ++j)
        {
            int ny = y + dy[i], nx = x + dx[i];
            tmp[y][x] = tmp[ny][nx];
            y = ny, x = nx;
        }
    }
    tmp[y][x + 1] = tmp_num;
}

void check()
{
    memcpy(tmp, arr, sizeof(arr));
    for (int i = 0; i < k; ++i)
    {
        for (int j = 1; j <= cmd[idx[i]].s; ++j)
        {
            turn(cmd[idx[i]].r - j - 1, cmd[idx[i]].c - j - 1, j * 2);
        }
    }
    for (int y = 0; y < n; ++y)
    {
        int tmp_sum = 0;
        for (int x = 0; x < m; ++x)
        {
            tmp_sum += tmp[y][x];
        }
        if (ret > tmp_sum)
            ret = tmp_sum;
    }
}

void dfs(int cnt)
{
    if (cnt == k)
    {
        check();
        return;
    }
    for (int i = 0; i < k; ++i)
    {
        if (!used[i])
        {
            used[i] = true;
            idx[cnt] = i;
            dfs(cnt + 1);
            used[i] = false;
        }
    }
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
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}