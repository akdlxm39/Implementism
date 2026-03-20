#include <iostream>

using namespace std;

int arr[1025][1025];
int tree[1025][1025];
int n, m;

void init()
{
    for (int y = 1; y <= n; ++y)
    {
        for (int x = 1; x <= n; ++x)
        {
            int xx = x + (x & -x);
            if (xx <= n)
                tree[y][xx] += tree[y][x];
        }
    }
    for (int x = 1; x <= n; ++x)
    {
        for (int y = 1; y <= n; ++y)
        {
            int yy = y + (y & -y);
            if (yy <= n)
                tree[yy][x] += tree[y][x];
        }
    }
}

void update(int y, int x, int diff)
{
    while (y <= n)
    {
        int xx = x;
        while (xx <= n)
        {
            tree[y][xx] += diff;
            xx += xx & -xx;
        }
        y += y & -y;
    }
}

int query(int y, int x)
{
    int result = 0;
    while (y > 0)
    {
        int xx = x;
        while (xx > 0)
        {
            result += tree[y][xx];
            xx -= xx & -xx;
        }
        y -= y & -y;
    }
    return result;
}

int rangeQuery(int sy, int sx, int ey, int ex)
{
    int result = 0;
    result += query(ey, ex);
    result -= query(sy - 1, ex);
    result -= query(ey, sx - 1);
    result += query(sy - 1, sx - 1);
    return result;
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> arr[i][j];
            tree[i][j] = arr[i][j];
        }
    }
    init();
    int w, y1, x1, y2, x2, c;
    for (int i = 0; i < m; ++i)
    {
        cin >> w;
        if (w == 0)
        {
            cin >> y1 >> x1 >> c;
            update(y1, x1, c - arr[y1][x1]);
            arr[y1][x1] = c;
        }
        else
        {
            cin >> y1 >> x1 >> y2 >> x2;
            cout << rangeQuery(y1, x1, y2, x2) << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}