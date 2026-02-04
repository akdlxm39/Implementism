#include <cstring>
#include <iostream>
#include <string>

using namespace std;

string arr[20001], tmp[20001];

bool check(string a, string b)
{
    if (a.length() == b.length())
        return a < b;
    return a.length() < b.length();
}

void merge(int left, int right)
{
    if (left + 1 == right)
        return;
    int mid = (left + right) / 2;
    int li = left, ri = mid, ti = left;
    while (li < mid && ri < right)
    {
        if (check(arr[li], arr[ri]))
            tmp[ti++] = arr[li++];
        else
            tmp[ti++] = arr[ri++];
    }
    while (li < mid)
        tmp[ti++] = arr[li++];
    while (ri < right)
        tmp[ti++] = arr[ri++];
    for (int it = left; it < right; ++it)
        arr[it] = tmp[it];
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
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    merge_sort(0, n);
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--)
        solve();

    return 0;
}
