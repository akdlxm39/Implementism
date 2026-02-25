#include <cstring>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

constexpr int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct Atom
{
    int y, x;
    int dir;
    int energy;
};

int ret;
int n;
int tmp[4001][4001];
unordered_map<int, Atom> atoms;
unordered_set<int> dead, out;

void init()
{
    ret = 0;
}

void input()
{
    cin >> n;
    int y, x, dir, energy;
    for (int i = 1; i <= n; ++i)
    {
        cin >> y >> x >> dir >> energy;
        atoms[i] = Atom{y * 2 + 2000, x * 2 + 2000, dir, energy};
    }
}

void simulation()
{
    dead.clear();
    out.clear();
    for (auto iter = atoms.begin(); iter != atoms.end(); ++iter)
    {
        Atom &cur = iter->second;
        cur.y += dy[cur.dir];
        cur.x += dx[cur.dir];
        if (cur.y < 0 || 4001 <= cur.y || cur.x < 0 || 4001 <= cur.x)
        {
            out.insert(iter->first);
            continue;
        }
        if (tmp[cur.y][cur.x] == 0)
        {
            tmp[cur.y][cur.x] = iter->first;
            continue;
        }
        else
        {
            dead.insert(tmp[cur.y][cur.x]);
            dead.insert(iter->first);
        }
    }
    for (auto iter = dead.begin(); iter != dead.end(); ++iter)
    {
        int cur = *iter;
        ret += atoms[cur].energy;
        tmp[atoms[cur].y][atoms[cur].x] = 0;
        atoms.erase(cur);
    }
    for (auto iter = out.begin(); iter != out.end(); ++iter)
    {
        int cur = *iter;
        atoms.erase(cur);
    }
    for (auto iter = atoms.begin(); iter != atoms.end(); ++iter)
    {
        tmp[iter->second.y][iter->second.x] = 0;
    }
}

void solve()
{
    while (true)
    {
        simulation();
        if (atoms.empty())
            break;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        init();
        input();
        solve();
        cout << '#' << tc << ' ' << ret << '\n';
    }

    return 0;
}