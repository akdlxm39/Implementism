#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, a;
vector<int> nums, unique_nums;

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> a;
        nums.push_back(a);
        unique_nums.push_back(a);
    }
    sort(unique_nums.begin(), unique_nums.end());
    unique_nums.erase(unique(unique_nums.begin(), unique_nums.end()), unique_nums.end());
    for (int num : nums)
    {
        cout << lower_bound(unique_nums.begin(), unique_nums.end(), num) - unique_nums.begin() << ' ';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("sample_input.txt", "r", stdin);

    solve();

    return 0;
}