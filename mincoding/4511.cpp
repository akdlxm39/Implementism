#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int dy[5] = {0, -1, 1, 0, 0}, dx[5] = {0, 0, 0, -1, 1};

struct Bomb
{
    int id, y, x;
};

struct compare
{
    bool operator()(Bomb a, Bomb b)
    {
        return a.id > b.id;
    }
};

int n, m;
bool bombed[1001][1001];
priority_queue<Bomb, vector<Bomb>, compare> pq;

int bomb()
{
    while (!pq.empty())
    {
        Bomb cur = pq.top();
        pq.pop();
        if (!bombed[cur.y][cur.x])
        {
            for (int i = 0; i < 5; ++i)
            {
                int y = cur.y + dy[i], x = cur.x + dx[i];
                if (0 <= y && y < 1000 && 0 <= x && x < 1000)
                    bombed[y][x] = true;
            }
            return cur.id;
        }
    }
    return -1;
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < n + m; ++i)
    {
        int b;
        cin >> b;
        if (b)
        {
            int y, x;
            cin >> y >> x;
            if (!bombed[y][x])
                pq.push({b, y, x});
        }
        else
            cout << bomb() << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}