#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <deque>
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

constexpr int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct Node
{
    int y;
    int x;
    int len;
    int from;
    int dir;
};

struct cmp
{
    bool operator()(Node a, Node b)
    {
        return a.len > b.len;
    }
};

int n, m, board_cnt, ret, sy, sx;
int board_input[11][11], board[11][11];

void input()
{
    memset(board, -1, sizeof(board));
    sy = sx = -1;
    cin >> n >> m;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            cin >> board_input[y][x];
            if (board_input[y][x] == 1 && sy == -1)
                sy = y, sx = x;
        }
    }
}

void solve()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({sy, sx, 0, board_cnt, -1});
    board[sy][sx] = board_cnt++;
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (cur.dir != -1)
        {
            int ny = cur.y + dy[cur.dir], nx = cur.x + dx[cur.dir];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx || board[ny][nx] != -1)
                continue;
            if (board_input[ny][nx] == 0)
                pq.push({ny, nx, cur.len + 1, cur.from, cur.dir});
            else if (cur.len >= 2)
            {
                ret += cur.len;
                pq.push({ny, nx, 0, board_cnt, -1});
                board[ny][nx] = board_cnt++;
            }
            continue;
        }
        for (int i = 0; i < 4; ++i)
        {
            int ny = cur.y + dy[i], nx = cur.x + dx[i];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx || board[ny][nx] != -1)
                continue;
            if (board_input[ny][nx] == 1)
            {
                board[ny][nx] = cur.from;
                pq.push({ny, nx, 0, cur.from, -1});
            }
            else
            {
                pq.push({ny, nx, 1, cur.from, i});
            }
        }
    }
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < m; ++x)
        {
            if (board_input[y][x] == 1 && board[y][x] == -1)
            {
                cout << "-1\n";
                return;
            }
        }
    }
    cout << ret << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    input();
    solve();

    return 0;
}