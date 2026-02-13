#include <iostream>
using namespace std;

int num[3] = {3, 2, 4};
bool used[3] = {0};

void dfs(int cur, int total)
{
    if (cur == 3)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (used[i])
                cout << num[i] << ' ';
        }
        cout << '\n';
        return;
    }

    if (total + num[cur] < 6)
    {
        used[cur] = true;
        dfs(cur + 1, total + num[cur]);
        used[cur] = false;
    }
    dfs(cur + 1, total);
}

int main()
{
    dfs(0, 0);
}
