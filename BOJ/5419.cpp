#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Island
{
    int x, y;
    bool operator<(const Island &other) const
    {
        if (x == other.x)
            return y < other.y;
        return x > other.x;
    }
};

int n, m;
long long ans;
vector<Island> islands;
vector<int> uni_y, tree;

void init()
{
    ans = 0;
    islands.clear();
    uni_y.clear();
}

void input()
{
    cin >> n;
    int y, x;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        islands.push_back({x, y});
        uni_y.push_back(y);
    }
}

void update(int idx)
{
    while (idx <= m)
    {
        tree[idx]++;
        idx += idx & -idx;
    }
}

int query(int idx)
{
    int ret = 0;
    while (idx > 0)
    {
        ret += tree[idx];
        idx -= idx & -idx;
    }
    return ret;
}

void solve()
{
    sort(islands.begin(), islands.end());
    sort(uni_y.begin(), uni_y.end());
    uni_y.erase(unique(uni_y.begin(), uni_y.end()), uni_y.end());
    m = uni_y.size();
    tree.assign(m + 1, 0);
    for (Island cur : islands)
    {
        int y = lower_bound(uni_y.begin(), uni_y.end(), cur.y) - uni_y.begin() + 1;
        ans += query(y);
        update(y);
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
        cout << ans << '\n';
    }

    return 0;
}