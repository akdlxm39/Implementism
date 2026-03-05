#include <iostream>
using namespace std;

constexpr int INF = 21e8;
constexpr int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct Point
{
    int y, x;
};

int n, k, board[9][9], visited[9][9], max_height, ans;

void init()
{
    max_height = 0;
    ans = 0;
}

void input()
{
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> board[i][j];
            if (max_height < board[i][j])
                max_height = board[i][j];
        }
    }
}

void bruteforce(int y, int x, int cur_len, bool worked)
{
    if (ans < cur_len)
        ans = cur_len;
    visited[y][x] = true;
    for (int i = 0; i < 4; ++i)
    {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || n <= nx || visited[ny][nx])
            continue;
        if (board[ny][nx] < board[y][x])
        {
            bruteforce(ny, nx, cur_len + 1, worked);
        }
        else if (!worked && board[ny][nx] - k < board[y][x])
        {
            int tmp = board[ny][nx];
            board[ny][nx] = board[y][x] - 1;
            bruteforce(ny, nx, cur_len + 1, true);
            board[ny][nx] = tmp;
        }
    }
    visited[y][x] = false;
}

void solve()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (board[i][j] == max_height)
                bruteforce(i, j, 1, false);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    for (int test_case = 1; test_case <= T; ++test_case)
    {
        init();
        input();
        solve();
        cout << "#" << test_case << ' ' << ans << '\n';
    }
}