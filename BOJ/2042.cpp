#include <iostream>
using namespace std;

#define ll long long

int n, m, k;
ll arr[1'000'001];
ll tree[4'000'001];

void init(int node, int left, int right)
{
    if (left == right)
    {
        tree[node] = arr[left - 1];
        return;
    }
    int mid = (left + right) / 2;
    init(node * 2, left, mid);
    init(node * 2 + 1, mid + 1, right);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int node, int left, int right, int idx, ll num)
{
    if (left == right)
    {
        tree[node] = num;
        return;
    }
    int mid = (left + right) / 2;
    if (left <= idx && idx <= mid)
        update(node * 2, left, mid, idx, num);
    else
        update(node * 2 + 1, mid + 1, right, idx, num);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int left, int right, int start, int end)
{
    if (end < left || right < start)
        return 0;
    if (start <= left && right <= end)
        return tree[node];
    int mid = (left + right) / 2;
    return query(node * 2, left, mid, start, end) + query(node * 2 + 1, mid + 1, right, start, end);
}

void solve()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    init(1, 1, n);
    for (int i = 0; i < m + k; ++i)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
            update(1, 1, n, b, c);
        else if (a == 2)
            cout << query(1, 1, n, b, c) << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}