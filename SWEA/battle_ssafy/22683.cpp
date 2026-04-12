#include <iostream>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

struct Point
{
    int y, x;
    Point operator+(Point other) const;
    bool isValid() const;
    char map() const;
};

struct Info
{
    Point pos;
    int dir, opCnt, restCutCnt;
    bool canMove();
};

const int MAX_SIZE = 10;
const Point DIR[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int n, k, ans;
string map_[MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE][4];
Point start;

inline Point Point::operator+(Point other) const
{
    return {y + other.y, x + other.x};
}

inline bool Point::isValid() const
{
    return 0 <= y && y < n && 0 <= x && x < n;
}

inline char Point::map() const
{
    return map_[y][x];
}

inline bool Info::canMove()
{
    if (pos.isValid())
    {
        if (pos.map() != 'T')
            return true;
        else if (restCutCnt-- > 0)
            return true;
    }
    return false;
}

void init()
{
    memset(visited, -1, sizeof(visited));
}

void input()
{
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        cin >> map_[i];
        size_t j = map_[i].find('X');
        if (j != string::npos)
            start.y = i, start.x = j;
    }
}

int bfs()
{
    queue<Info> q;
    q.push({start, 0, 0, k});
    visited[start.y][start.x][0] = k;
    auto pushIfValid = [&](Info nxt) {
        if (visited[nxt.pos.y][nxt.pos.x][nxt.dir] < nxt.restCutCnt)
        {
            visited[nxt.pos.y][nxt.pos.x][nxt.dir] = nxt.restCutCnt;
            q.push(nxt);
        }
    };
    while (!q.empty())
    {
        Info cur = q.front();
        q.pop();
        if (cur.pos.map() == 'Y')
            return cur.opCnt;
        // 전진
        Info nxt = {cur.pos + DIR[cur.dir], cur.dir, cur.opCnt + 1, cur.restCutCnt};
        if (nxt.canMove())
            pushIfValid(nxt);
        // 우회전
        pushIfValid({cur.pos, (cur.dir + 1) % 4, cur.opCnt + 1, cur.restCutCnt});
        // 좌회전
        pushIfValid({cur.pos, (cur.dir + 3) % 4, cur.opCnt + 1, cur.restCutCnt});
    }
    return -1;
}

void solve()
{
    ans = bfs();
}

void output(int testCase)
{
    cout << '#' << testCase << ' ' << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int testCase = 1; testCase <= T; ++testCase)
    {
        init();
        input();
        solve();
        output(testCase);
    }

    return 0;
}