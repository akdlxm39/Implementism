#include <iostream>

using namespace std;

void init()
{
}

void input()
{
}

void solve()
{
}

void output(int testCase)
{
    cout << '#' << testCase << ' ' << "" << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    int T = 1;
    cin >> T;
    for (int testCase = 1; testCase <= T; ++testCase)
    {
        init();
        input();
        solve();
        output(testCase);
    }

    return 0;
}