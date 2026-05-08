#include <vector>
using namespace std;

int solution(int n, vector<int> money)
{
    vector<int> changes(n + 1, 0);
    changes[0] = 1;
    for (auto m : money)
    {
        for (int i = m; i <= n; ++i)
        {
            changes[i] += changes[i - m];
            changes[i] %= 1'000'000'007;
        }
    }
    return changes[n];
}