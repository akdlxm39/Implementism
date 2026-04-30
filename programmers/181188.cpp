#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> targets)
{
    int answer = 0;
    sort(targets.begin(), targets.end(), [](const vector<int> &a, const vector<int> &b) { return a[1] < b[1]; });
    int cur = 0;
    for (const auto &target : targets)
    {
        if (cur <= target[0])
        {
            cur = target[1];
            answer++;
        }
    }
    return answer;
}