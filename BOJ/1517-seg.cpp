// https://www.acmicpc.net/problem/1517 버블 소트
#include <algorithm>
#include <iostream>

using namespace std;
#define pii pair<int, int>

long long ret;
int n;
pii arr[500'001];
int seg_tree[2'000'001];

void input()
{
    ret = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i].first;
        arr[i].second = i;
    }
}

int query(int node, int left, int right, int start, int end)
{
    if (end < left || right < start)
        return 0;
    if (start <= left && right <= end)
        return seg_tree[node];
    int mid = (left + right) / 2;
    return query(node * 2, left, mid, start, end) + query(node * 2 + 1, mid + 1, right, start, end);
}

void update(int node, int left, int right, int idx)
{
    seg_tree[node]++;
    if (left == right)
        return;
    int mid = (left + right) / 2;
    if (left <= idx && idx <= mid)
        update(node * 2, left, mid, idx);
    else
        update(node * 2 + 1, mid + 1, right, idx);
}

void solve()
{
    sort(arr, arr + n);
    for (int i = 0; i < n; ++i)
    {
        ret += query(1, 0, n - 1, arr[i].second + 1, n - 1);
        update(1, 0, n - 1, arr[i].second);
    }
    cout << ret << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    solve();

    return 0;
}