#include <iostream>

using namespace std;

bool arr[987'654'323];

void solve()
{
    int n;
    cin >> n;
    if (n < 10)
    {
        cout << n << '\n';
        return;
    }
    int l = 1;
    for (int i = 0; i < 987654322; ++i)
    {
        if (!arr[i])
            continue;
        if (i / l == 10)
            l *= 10;
        for (int j = i / l + 1; j <= 9; ++j)
        {
            arr[i + j * l * 10] = true;
        }
        if (--n == 0)
        {
            cout << i << '\n';
            break;
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