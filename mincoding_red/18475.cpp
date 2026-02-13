#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// x x x x x x x
// x 0 0 1 2 2 x
// x 0 0 1 2 2 x
// x 3 3 4 5 5 x
// x 6 6 7 8 8 x
// x 6 6 7 8 8 x
// x x x x x x x
constexpr int turn[4][9] = {
    // 내가 보는 방향마다, 각 구역을 가는데에 드는 최소 우회전 수
    {3, 3, 3, 3, 0, 0, 2, 1, 1}, // 오른쪽을 볼 때
    {2, 3, 3, 1, 0, 3, 1, 0, 3}, // 아래쪽을 볼 때
    {1, 1, 2, 0, 0, 3, 3, 3, 3}, // 왼쪽을 볼 때
    {3, 0, 1, 3, 0, 1, 3, 3, 2}, // 위쪽을 볼 때
};

struct Apple
{
    int id, y, x;
};
bool compare(const Apple &a, const Apple &b)
{
    return a.id < b.id;
}

int ret;
int n;
vector<Apple> apples;

void init()
{
    ret = 0;
    apples.clear();
}

void input()
{
    cin >> n;
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            int a;
            cin >> a;
            // 맵의 형태로 입력받았지만 필요한 것은 사과의 id와 위치
            if (a != 0)
                apples.push_back({a, y, x});
        }
    }
    // 사과의 id를 기준으로 오름차순 정렬
    sort(apples.begin(), apples.end(), compare);
}

void solve()
{
    // x x x x x x x
    // x 0 0 1 2 2 x
    // x 0 0 1 2 2 x
    // x 3 3 4 5 5 x
    // x 6 6 7 8 8 x
    // x 6 6 7 8 8 x
    // x x x x x x x
    int dir = 0, y = 0, x = 0;
    for (Apple apple : apples)
    {
        int area = 0;
        // y를 기준으로 구역 선택
        if (apple.y == y)
            area += 3;
        else if (apple.y > y)
            area += 6;
        // x를 기준으로 구역 선택
        if (apple.x == x)
            area += 1;
        else if (apple.x > x)
            area += 2;
        // 내가 바라보는 방향과 사과가 위치한 구역으로 우회전수를 구함
        ret += turn[dir][area];
        y = apple.y;
        x = apple.x;
        dir = (dir + turn[dir][area]) % 4;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}