#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
const int HASH_SIZE = 10007;

struct Edge
{
    int id;
    int from;
    int to;
    int cost;
    int nxtEdge;
    int nxtRevEdge;
    int nxtHash;
    bool removed;
} edgePool[6507];
int edgeCnt = 0;
int edgeMap[HASH_SIZE];
int edgeHead[1007];
int revEdgeHead[1007];
int n, k;

void add(int mId, int sCity, int eCity, int mTime);

void init(int N, int K, int mId[], int sCity[], int eCity[], int mTime[])
{
    edgeCnt = 0;
    memset(edgeMap, -1, sizeof(edgeMap));
    memset(edgeHead, -1, sizeof(edgeHead));
    memset(revEdgeHead, -1, sizeof(revEdgeHead));
    n = N;
    k = K;
    for (int i = 0; i < k; ++i)
        add(mId[i], sCity[i], eCity[i], mTime[i]);
    return;
}

void add(int mId, int sCity, int eCity, int mTime)
{
    edgePool[edgeCnt].id = mId;
    edgePool[edgeCnt].from = sCity;
    edgePool[edgeCnt].to = eCity;
    edgePool[edgeCnt].cost = mTime;
    edgePool[edgeCnt].removed = false;

    edgePool[edgeCnt].nxtEdge = edgeHead[sCity];
    edgeHead[sCity] = edgeCnt;

    edgePool[edgeCnt].nxtRevEdge = revEdgeHead[eCity];
    revEdgeHead[eCity] = edgeCnt;

    edgePool[edgeCnt].nxtHash = edgeMap[mId % HASH_SIZE];
    edgeMap[mId % HASH_SIZE] = edgeCnt;

    edgeCnt++;
    return;
}

void remove(int mId)
{
    int cur = edgeMap[mId % HASH_SIZE];
    while (cur != -1)
    {
        if (edgePool[cur].id == mId)
        {
            edgePool[cur].removed = true;
            return;
        }
        cur = edgePool[cur].nxtHash;
    }
    return;
}

struct Node
{
    int id, dist, guess;
    bool operator<(const Node &other) const
    {
        return guess == other.guess ? dist > other.dist : guess > other.guess;
    }
};

int dist[1007];
int revDist[1007];
int nxtCity[1007];
int fromEdge[1007];
int epoch[1007];
int epochCnt = 0;
int revEpoch[1007];
int revEpochCnt = 0;

int dijkstra(int sCity, int eCity)
{
    ++epochCnt;
    std::priority_queue<Node> pq;
    pq.push({sCity, 0, 0});
    dist[sCity] = 0;
    fromEdge[sCity] = 0;
    epoch[sCity] = epochCnt;
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (cur.id == eCity)
            return dist[eCity];
        if (epoch[cur.id] == epochCnt && dist[cur.id] < cur.dist)
            continue;
        for (int edgeIdx = edgeHead[cur.id]; edgeIdx != -1; edgeIdx = edgePool[edgeIdx].nxtEdge)
        {
            if (edgePool[edgeIdx].removed)
                continue;
            int nxtId = edgePool[edgeIdx].to;
            int nxtDist = cur.dist + edgePool[edgeIdx].cost;
            if (epoch[nxtId] == epochCnt && dist[nxtId] <= nxtDist)
                continue;
            pq.push({nxtId, nxtDist, 0});
            dist[nxtId] = nxtDist;
            fromEdge[nxtId] = edgeIdx;
            epoch[nxtId] = epochCnt;
        }
    }
    return INT_MAX;
}

void revDijkstra(int eCity)
{
    revEpochCnt++;
    std::priority_queue<Node> pq;
    pq.push({eCity, 0, 0});
    revDist[eCity] = 0;
    revEpoch[eCity] = revEpochCnt;
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (revEpoch[cur.id] == revEpochCnt && revDist[cur.id] < cur.dist)
            continue;
        for (int edgeIdx = revEdgeHead[cur.id]; edgeIdx != -1; edgeIdx = edgePool[edgeIdx].nxtRevEdge)
        {
            if (edgePool[edgeIdx].removed)
                continue;
            int nxtId = edgePool[edgeIdx].from;
            int nxtDist = cur.dist + edgePool[edgeIdx].cost;
            if (revEpoch[nxtId] == revEpochCnt && revDist[nxtId] <= nxtDist)
                continue;
            pq.push({nxtId, nxtDist, 0});
            revDist[nxtId] = nxtDist;
            revEpoch[nxtId] = revEpochCnt;
        }
    }
}

int Astar(int sCity, int eCity)
{
    epochCnt++;
    if (revEpoch[sCity] != revEpochCnt)
        return INT_MAX;
    std::priority_queue<Node> pq;
    pq.push({sCity, 0, revDist[sCity]});
    dist[sCity] = 0;
    epoch[sCity] = epochCnt;
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        if (cur.id == eCity)
            return dist[eCity];
        if (epoch[cur.id] == epochCnt && dist[cur.id] < cur.dist)
            continue;
        for (int edgeIdx = edgeHead[cur.id]; edgeIdx != -1; edgeIdx = edgePool[edgeIdx].nxtEdge)
        {
            if (edgePool[edgeIdx].removed)
                continue;
            int nxtId = edgePool[edgeIdx].to;
            if (revEpoch[nxtId] != revEpochCnt)
                continue;
            int nxtDist = cur.dist + edgePool[edgeIdx].cost;
            if (epoch[nxtId] == epochCnt && dist[nxtId] <= nxtDist)
                continue;
            pq.push({nxtId, nxtDist, nxtDist + revDist[nxtId]});
            dist[nxtId] = nxtDist;
            epoch[nxtId] = epochCnt;
        }
    }
    return INT_MAX;
}

int calculate(int sCity, int eCity)
{
    int initDist = dijkstra(sCity, eCity);
    if (initDist == INT_MAX)
        return -1;
    revDijkstra(eCity);

    std::vector<int> usedEdges;
    int cur = eCity;
    while (cur != sCity)
    {
        int edgeIdx = fromEdge[cur];
        usedEdges.push_back(edgeIdx);
        cur = edgePool[edgeIdx].from;
    }

    int maxDelay = 0;
    for (int edgeIdx : usedEdges)
    {
        edgePool[edgeIdx].removed = true;
        int destroyDist = Astar(sCity, eCity);
        edgePool[edgeIdx].removed = false;
        if (destroyDist == INT_MAX)
            return -1;
        maxDelay = std::max(maxDelay, destroyDist - initDist);
    }
    return maxDelay;
}