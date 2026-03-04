#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX = 2'000'001;
// constexpr int MAX = 500'001;

int n, a;
vector<int> speed1, speed2;
int tree[MAX];

// void update(int idx)
// {
//     while (idx <= n)
//     {
//         tree[idx]++;
//         idx += idx & -idx;
//     }
// }

// int query(int idx)
// {
//     int ret = 0;
//     while (idx > 0)
//     {
//         ret += tree[idx];
//         idx -= idx & -idx;
//     }
//     return ret;
// }

void update(int node, int left, int right, int idx)
{
    tree[node]++;
    if (left == right)
        return;
    int mid = left + (right - left) / 2;
    if (left <= idx && idx <= mid)
        update(node * 2, left, mid, idx);
    else
        update(node * 2 + 1, mid + 1, right, idx);
}

int query(int node, int left, int right, int start, int end)
{
    if (right < start || end < left)
        return 0;
    if (start <= left && right <= end)
        return tree[node];
    int mid = left + (right - left) / 2;
    int l = query(node * 2, left, mid, start, end);
    int r = query(node * 2 + 1, mid + 1, right, start, end);
    return l + r;
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> a;
        speed1.push_back(a);
        speed2.push_back(a);
    }
    sort(speed2.begin(), speed2.end());
    for (int rank = 0; rank < n; ++rank)
    {
        int new_speed = lower_bound(speed2.begin(), speed2.end(), speed1[rank]) - speed2.begin() + 1;
        int new_rank = rank + 1 - query(1, 1, n, 1, new_speed);
        update(1, 1, n, new_speed);
        // int new_rank = rank + 1 - query(new_speed);
        // update(new_speed);
        cout << new_rank << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    solve();

    return 0;
}