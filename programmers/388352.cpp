#include <string>
#include <vector>

using namespace std;

int dfs(int n, int idx, vector<int> &v, int m, vector<vector<int>> &q, vector<int> &ans)
{
    if (v.size() == 5)
    {
        for (int i = 0; i < m; ++i)
        {
            int cnt = 0;
            for (int num : q[i])
                for (int num2 : v)
                    if (num == num2)
                        cnt++;
            if (cnt != ans[i])
                return 0;
        }
        return 1;
    }
    int ret = 0;
    for (int i = idx; i <= n; ++i)
    {
        v.push_back(i);
        ret += dfs(n, i + 1, v, m, q, ans);
        v.pop_back();
    }
    return ret;
}

int solution(int n, vector<vector<int>> q, vector<int> ans)
{
    int answer = 0;
    int m = q.size();
    vector<int> v;
    answer = dfs(n, 1, v, m, q, ans);

    return answer;
}