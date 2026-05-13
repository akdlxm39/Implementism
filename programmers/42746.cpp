#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmd(string a, string b)
{
    a += a + a;
    b += b + b;
    for (int i = 0; i < min(a.length(), b.length()); ++i)
    {
        if (a[i] != b[i])
            return a[i] > b[i];
    }
    return false;
}

string solution(vector<int> numbers)
{
    vector<string> nums;
    for (auto n : numbers)
        nums.push_back(to_string(n));
    sort(nums.begin(), nums.end(), cmd);
    string answer = "";
    for (auto n : nums)
        answer += n;
    if (nums[0] == "0")
        answer = "0";
    return answer;
}