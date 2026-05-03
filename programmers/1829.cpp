#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Point
{
    int y, x;
    Point operator+(Point other) const
    {
        return {y + other.y, x + other.x};
    }
};
const Point DIR[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int bfs(int y, int x, int m, int n, vector<vector<int>> &picture)
{
    int cnt = 0, color = picture[y][x];
    queue<Point> q;
    q.push({y, x});
    picture[y][x] = 0;
    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();
        for (Point d : DIR)
        {
            Point nxt = cur + d;
            if (nxt.y < 0 || m <= nxt.y || nxt.x < 0 || n <= nxt.x || picture[nxt.y][nxt.x] != color)
                continue;
            q.push(nxt);
            picture[nxt.y][nxt.x] = 0;
        }
        cnt++;
    }
    return cnt;
}

vector<int> solution(int m, int n, vector<vector<int>> picture)
{
    int number_of_area = 0;
    int max_size_of_one_area = 0;

    for (int y = 0; y < m; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            if (picture[y][x] != 0)
            {
                number_of_area++;
                max_size_of_one_area = max(max_size_of_one_area, bfs(y, x, m, n, picture));
            }
        }
    }

    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}