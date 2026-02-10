#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n;
priority_queue<int> max_heap;
priority_queue<int, vector<int>, greater<int>> min_heap;

void solve()
{
    max_heap.push(500);
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            int x;
            cin >> x;
            max_heap.push(x);
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
        max_heap.push(min_heap.top());
        min_heap.pop();

        cout << max_heap.top() << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}