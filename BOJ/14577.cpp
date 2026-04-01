#include <iostream>

using namespace std;

typedef long long ll;

const ll MAX = 1'000'000'000'000'000'000;

int n, m;

struct Node
{
    int leftChild, rightChild, cnt;
} nodes[10'000'000];
int nodeCnt;
int root;

int addNode()
{
    int id = nodeCnt++;
    nodes[id].leftChild = nodes[id].rightChild = -1;
    nodes[id].cnt = 0;
    return id;
}

void update(int cur, ll left, ll right, ll idx, int num)
{
    nodes[cur].cnt += num;
    if (left == right)
        return;
    ll mid = left + (right - left) / 2;
    if (left <= idx && idx <= mid)
    {
        if (nodes[cur].leftChild == -1)
            nodes[cur].leftChild = addNode();
        update(nodes[cur].leftChild, left, mid, idx, num);
    }
    else
    {
        if (nodes[cur].rightChild == -1)
            nodes[cur].rightChild = addNode();
        update(nodes[cur].rightChild, mid + 1, right, idx, num);
    }
}

int cntQuery(int cur, ll left, ll right, ll start, ll end)
{
    if (end < left || right < start)
        return 0;
    if (start <= left && right <= end)
        return nodes[cur].cnt;
    ll mid = left + (right - left) / 2;
    int ret = 0;
    if (nodes[cur].leftChild != -1)
        ret += cntQuery(nodes[cur].leftChild, left, mid, start, end);
    if (nodes[cur].rightChild != -1)
        ret += cntQuery(nodes[cur].rightChild, mid + 1, right, start, end);
    return ret;
}

ll TthQuery(int cur, ll left, ll right, int t)
{
    if (left == right)
        return left;
    ll mid = left + (right - left) / 2;
    if (nodes[cur].rightChild != -1)
    {
        if (nodes[nodes[cur].rightChild].cnt >= t)
            return TthQuery(nodes[cur].rightChild, mid + 1, right, t);
        else
            t -= nodes[nodes[cur].rightChild].cnt;
    }
    return TthQuery(nodes[cur].leftChild, left, mid, t);
}

ll snows[100'001];

void solve()
{
    nodeCnt = 0;
    root = addNode();

    cin >> n >> m;
    ll x;
    for (int i = 1; i <= n; ++i)
    {
        cin >> snows[i];
        update(root, 0, MAX, snows[i], 1);
    }
    int q;
    ll a, b;
    for (int i = 0; i < m; ++i)
    {
        cin >> q >> a;
        if (q == 4)
            cout << TthQuery(root, 0, MAX, a) << '\n';
        else
        {
            cin >> b;
            if (q == 1)
            {
                update(root, 0, MAX, snows[a], -1);
                snows[a] += b;
                update(root, 0, MAX, snows[a], 1);
            }
            else if (q == 2)
            {
                update(root, 0, MAX, snows[a], -1);
                snows[a] -= b;
                update(root, 0, MAX, snows[a], 1);
            }
            else if (q == 3)
                cout << cntQuery(root, 0, MAX, a, b) << '\n';
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