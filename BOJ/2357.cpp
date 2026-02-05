#include <algorithm>
#include <iostream>
#include <tuple>

using namespace std;

constexpr int MIN = 0, MAX = 1'000'000'001;

int n, m;
int min_tree[400'001], max_tree[400'001];

void init(int node, int left, int right)
{
    if (left == right)
    {
        cin >> min_tree[node];
        max_tree[node] = min_tree[node];
        return;
    }
    int mid = left + (right - left) / 2;
    init(node * 2, left, mid);
    init(node * 2 + 1, mid + 1, right);
    min_tree[node] = min(min_tree[node * 2], min_tree[node * 2 + 1]);
    max_tree[node] = max(max_tree[node * 2], max_tree[node * 2 + 1]);
}

tuple<int, int> query(int node, int left, int right, int start, int end)
{
    if (end < left || right < start)
        return {MAX, MIN};
    if (start <= left && right <= end)
        return {min_tree[node], max_tree[node]};
    int mid = left + (right - left) / 2;
    int left_min, right_min, left_max, right_max;
    tie(left_min, left_max) = query(node * 2, left, mid, start, end);
    tie(right_min, right_max) = query(node * 2 + 1, mid + 1, right, start, end);
    return {min(left_min, right_min), max(left_max, right_max)};
}

void solve()
{
    cin >> n >> m;
    init(1, 1, n);
    while (m--)
    {
        int a, b, min_ans, max_ans;
        cin >> a >> b;
        tie(min_ans, max_ans) = query(1, 1, n, a, b);
        cout << min_ans << ' ' << max_ans << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}