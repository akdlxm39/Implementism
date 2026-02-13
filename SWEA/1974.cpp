#include <cstring>
#include <iostream>
using namespace std;

int ret;
int sudoku[10][10];
bool visited[10];

void input()
{
    ret = 1;
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cin >> sudoku[i][j];
        }
    }
}

void solve()
{
    for (int i = 0; i < 9; ++i)
    {
        memset(visited, 0, sizeof(visited));
        for (int j = 0; j < 9; ++j)
        {
            if (visited[sudoku[i][j]])
            {
                ret = 0;
                return;
            }
            visited[sudoku[i][j]] = true;
        }
    }
    for (int j = 0; j < 9; ++j)
    {
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < 9; ++i)
        {
            if (visited[sudoku[i][j]])
            {
                ret = 0;
                return;
            }
            visited[sudoku[i][j]] = true;
        }
    }
    for (int k = 0; k < 9; ++k)
    {
        memset(visited, 0, sizeof(visited));
        for (int l = 0; l < 9; ++l)
        {
            int i = k / 3 * 3 + l / 3, j = k % 3 * 3 + l % 3;
            if (visited[sudoku[i][j]])
            {
                ret = 0;
                return;
            }
            visited[sudoku[i][j]] = true;
        }
    }
    ret = 1;
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        input();
        solve();
        cout << '#' << tc << ' ' << ret << '\n';
    }
}