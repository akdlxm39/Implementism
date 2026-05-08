#include <vector>
using namespace std;

int solution(int n, vector<int> money)
{
    vector<int> changeCnt(n + 1, 0);
    changeCnt[0] = 1;
    for (auto m : money)
    {
        for (int i = m; i <= n; ++i)
        {
            changeCnt[i] += changeCnt[i - m];
            changeCnt[i] %= 1'000'000'007;
        }
    }
    return changeCnt[n];
}