// https://www.acmicpc.net/problem/1517 버블 소트
#include <iostream>
using namespace std;

long long ret;
int n, arr[500'001], tmp[500'001];

void input()
{
    ret = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
}

void merge(int left, int right)
{
    int mid = (left + right) / 2;
    int li = left, ri = mid, ti = left;

    while (li < mid && ri < right)
    {
        if (arr[li] <= arr[ri])
            tmp[ti++] = arr[li++];
        else
        {
            ret += mid - li;
            tmp[ti++] = arr[ri++];
        }
    }
    while (li < mid)
        tmp[ti++] = arr[li++];
    while (ri < right)
        tmp[ti++] = arr[ri++];

    for (int i = left; i < right; ++i)
    {
        arr[i] = tmp[i];
    }
}

void merge_sort(int left, int right)
{
    if (left + 1 == right)
        return;
    int mid = (left + right) / 2;
    merge_sort(left, mid);
    merge_sort(mid, right);
    merge(left, right);
}

void solve()
{
    merge_sort(0, n);
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