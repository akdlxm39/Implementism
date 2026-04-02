#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int l, r, c;
char map_[31][31][31];
int dist_[31][31][31];
struct Pos
{
    int z, y, x;
    inline Pos operator+(const Pos &other) const
    {
        return {z + other.z, y + other.y, x + other.x};
    }
    inline bool isValid() const
    {
        return 0 <= z && z < l && 0 <= y && y < r && 0 <= x && x < c;
    }
    inline char map() const
    {
        return map_[z][y][x];
    }
    inline int &dist() const
    {
        return dist_[z][y][x];
    }
};
const Pos DIR[6] = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};
queue<Pos> q;

bool solve()
{
    cin >> l >> r >> c;
    if (l == 0)
        return false;
    q = queue<Pos>();
    memset(dist_, -1, sizeof(dist_));
    for (int z = 0; z < l; ++z)
    {
        for (int y = 0; y < r; ++y)
        {
            cin >> map_[z][y];
            for (int x = 0; x < c; ++x)
                if (map_[z][y][x] == 'S')
                {
                    q.push({z, y, x});
                    dist_[z][y][x] = 0;
                }
        }
    }
    while (!q.empty())
    {
        Pos cur = q.front();
        q.pop();
        for (Pos d : DIR)
        {
            Pos nxt = cur + d;
            if (!nxt.isValid() || nxt.dist() != -1 || nxt.map() == '#')
                continue;
            nxt.dist() = cur.dist() + 1;
            if (nxt.map() == 'E')
            {
                cout << "Escaped in " << nxt.dist() << " minute(s).\n";
                return true;
            }
            q.push(nxt);
        }
    }
    cout << "Trapped!\n";
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (solve())
        ;

    return 0;
}