#include <iostream>
using namespace std;

constexpr int dy[4] = {0, -1, 0, 1}, dx[4] = {1, 0, -1, 0};

int ret;
int n, m;
int map_[10][10], tmp[10][10];
int grow_time[10][10];

void init()
{
    ret = 0;
}

void input()
{
    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> map_[y][x];
            if (map_[y][x] == 1)
                map_[y][x] = -1;
        }
    }
}

void simulation(int y, int x, int d)
{
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            grow_time[y][x] = 5;
            tmp[y][x] = map_[y][x];
        }
    }
    int cnt = 0;
    for (int time = 0; time < m; ++time)
    {
        int ny, nx, di;
        for (di = 3; di <= 6; ++di)
        {
            int nd = (d + di) % 4;
            ny = y + dy[nd], nx = x + dx[nd];
            if (tmp[ny][nx] != -1 && tmp[ny][nx] <= time)
                break;
        }
        if (tmp[y][x] == 0 && di < 7)
        {
            tmp[y][x] = time + grow_time[y][x];
            grow_time[y][x]++;
        }
        else if (tmp[y][x] != 0 && tmp[y][x] < time)
        {
            cnt++;
            tmp[y][x] = 0;
        }
        if (di < 7)
            y = ny, x = nx, d = (d + di) % 4;
    }
    if (ret < cnt)
        ret = cnt;
}

void solve()
{
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            if (map_[y][x] == -1)
                continue;
            for (int d = 0; d < 4; ++d)
            {
                simulation(y, x, d);
            }
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
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}