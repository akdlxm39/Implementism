#include <iostream>
#include <algorithm>

using namespace std;

int n, len, max_len;
int tanghuru[200'000];
int fruit[10];

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> tanghuru[i];
    int l = 0, r = 0, cnt = 0;
    while (r <= n)
    {
        fruit[tanghuru[r++]]++;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}