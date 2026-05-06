#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int bruteforce(int total, int cur, int a, int b, const vector<vector<int>> &info, int n, int m)
{
    if (cur == total)
        return a;
    int ret = INF;
    if (a + info[cur][0] < n)
        ret = min(ret, bruteforce(total, cur + 1, a + info[cur][0], b, info, n, m));
    if (b + info[cur][1] < m)
        ret = min(ret, bruteforce(total, cur + 1, a, b + info[cur][1], info, n, m));
    return ret;
}

int solution(vector<vector<int>> info, int n, int m)
{
    int answer = bruteforce(info.size(), 0, 0, 0, info, n, m);
    if (answer == INF)
        answer = -1;
    return answer;
}