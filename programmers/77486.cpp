#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount)
{
    unordered_map<string, int> map;
    vector<int> parent;
    vector<int> answer;
    int cnt = 0;
    for (auto e : enroll)
        map[e] = cnt++;
    parent.assign(cnt, -1);
    answer.resize(cnt);
    for (int i = 0; i < cnt; ++i)
        if (referral[i] != "-")
            parent[map[enroll[i]]] = map[referral[i]];
    for (int i = 0; i < seller.size(); ++i)
    {
        int cur = map[seller[i]];
        int profit = amount[i] * 100;
        while (cur != -1)
        {
            int nxt_profit = profit / 10;
            answer[cur] += profit - nxt_profit;
            profit = nxt_profit;
            cur = parent[cur];
        }
    }

    return answer;
}