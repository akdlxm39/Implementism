#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define MAP_SIZE_MAX 350
#define GATE_CNT_MAX 201
#define MAX 150'000

constexpr int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
struct Point
{
    int y, x;
    int dist;
};
struct Edge
{
    int to, dist;
};

int map_size, stamina;
int _map[MAP_SIZE_MAX][MAP_SIZE_MAX];
bool visited[MAP_SIZE_MAX][MAP_SIZE_MAX];
int gate_cnt;
Point gate_yx[GATE_CNT_MAX];
vector<Edge> adj_list[GATE_CNT_MAX];
bool removed[GATE_CNT_MAX];
int dist[GATE_CNT_MAX];

void init(int N, int mMaxStamina, int mMap[MAP_SIZE_MAX][MAP_SIZE_MAX])
{
    map_size = N;
    stamina = mMaxStamina;
    for (int y = 0; y < map_size; ++y)
        for (int x = 0; x < map_size; ++x)
            _map[y][x] = mMap[y][x] ? -1 : 0;
    gate_cnt = 0;
    for (int i = 0; i < GATE_CNT_MAX; ++i)
        adj_list[i].clear();
    memset(removed, false, sizeof(removed));
    return;
}

void addGate(int mGateID, int mRow, int mCol)
{
    for (int y = 0; y < map_size; ++y)
        for (int x = 0; x < map_size; ++x)
            visited[y][x] = false;
    _map[mRow][mCol] = mGateID;
    gate_cnt = mGateID;
    queue<Point> q;
    visited[mRow][mCol] = true;
    q.push({mRow, mCol, 0});
    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();
        if (cur.dist == stamina)
            break;
        for (int i = 0; i < 4; ++i)
        {
            int ny = cur.y + dy[i], nx = cur.x + dx[i];
            if (visited[ny][nx] || _map[ny][nx] == -1)
                continue;
            if (_map[ny][nx])
            {
                adj_list[mGateID].push_back({_map[ny][nx], cur.dist + 1});
                adj_list[_map[ny][nx]].push_back({mGateID, cur.dist + 1});
            }
            visited[ny][nx] = true;
            q.push({ny, nx, cur.dist + 1});
        }
    }
    return;
}

void removeGate(int mGateID)
{
    for (int yx = 0; yx < map_size * map_size; ++yx)
    {
        if (_map[yx / map_size][yx % map_size] == mGateID)
        {
            _map[yx / map_size][yx % map_size] = 0;
            break;
        }
    }
    removed[mGateID] = true;
    return;
}

int getMinTime(int mStartGateID, int mEndGateID)
{
    for (int i = 0; i < GATE_CNT_MAX; ++i)
        dist[i] = MAX;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, mStartGateID});
    dist[mStartGateID] = 0;
    while (!pq.empty())
    {
        pair<int, int> cur = pq.top();
        pq.pop();
        if (dist[cur.second] < cur.first)
            continue;
        if (cur.second == mEndGateID)
            break;
        for (Edge e : adj_list[cur.second])
        {
            if (removed[e.to])
                continue;
            int nxt_dist = cur.first + e.dist;
            if (dist[e.to] <= nxt_dist)
                continue;
            dist[e.to] = nxt_dist;
            pq.push({nxt_dist, e.to});
        }
    }
    return (dist[mEndGateID] == MAX) ? -1 : dist[mEndGateID];
}