#include <iostream>
using namespace std;

struct Balloon
{
    int num, left, right;
};

int ret;
int n, head;
Balloon arr[11];

void init()
{
    ret = 0;
    head = 0;
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i].num;
        arr[i].left = i - 1;
        arr[i].right = i + 1;
    }
    arr[0].left = arr[n - 1].right = -1;
}

int pop(int cur)
{
    int res = 1;
    if (arr[cur].left == -1 && arr[cur].right == -1)
        return arr[cur].num;
    if (arr[cur].left != -1)
    {
        res *= arr[arr[cur].left].num;
        arr[arr[cur].left].right = arr[cur].right;
    }
    else
        head = arr[cur].right;
    if (arr[cur].right != -1)
    {
        res *= arr[arr[cur].right].num;
        arr[arr[cur].right].left = arr[cur].left;
    }
    return res;
}

void undo(int cur)
{
    if (arr[cur].left != -1)
    {
        arr[arr[cur].left].right = cur;
    }
    else
        head = cur;
    if (arr[cur].right != -1)
    {
        arr[arr[cur].right].left = cur;
    }
}

void dfs(int cnt, int total)
{
    if (cnt == n)
    {
        if (ret < total)
            ret = total;
        return;
    }
    for (int cur = head; cur != -1; cur = arr[cur].right)
    {
        dfs(cnt + 1, total + pop(cur));
        undo(cur);
    }
}

void solve()
{
    dfs(0, 0);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}