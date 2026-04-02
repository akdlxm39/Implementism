#include <iostream>
#include <vector>

using namespace std;

int n;
int nums[101];
int state[101];
bool isCycle[101];
int ans;
vector<int> st;

int checkCycle(int cur)
{
    if (state[cur] == 1)
        return cur;
    if (state[cur] == 2)
        return 0;
    state[cur] = 1;
    st.push_back(cur);
    int root = checkCycle(nums[cur]);
    state[cur] = 2;
    if (root == cur)
    {
        while (true)
        {
            int tmp = st.back();
            st.pop_back();
            isCycle[tmp] = true;
            ans++;
            if (cur == tmp)
                break;
        }
        return 0;
    }
    return root;
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> nums[i];
    for (int i = 1; i <= n; ++i)
    {
        if (state[i] == 0)
        {
            st.clear();
            checkCycle(i);
        }
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i)
        if (isCycle[i])
            cout << i << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}