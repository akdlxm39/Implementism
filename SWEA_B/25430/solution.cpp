#include <cstring>
#include <utility>
#include <algorithm>
#define MAX_DIST 500'001

enum Where
{
    COFFEE,
    BAKERY,
    WHERE_SIZE
};

struct Edge
{
    int to;
    int dist;
    int nxtEdge;
} edgePool[64001];
int edgeCnt;

struct Node
{
    int edges;
    int dist[WHERE_SIZE];
    int calcCnt[WHERE_SIZE];
} nodes[10001];
int calcCnt = 0;
int nodeCnt;

void add(int sBuilding, int eBuilding, int mDistance);

void init(int N, int K, int sBuilding[], int eBuilding[], int mDistance[])
{
    edgeCnt = 0;
    nodeCnt = N;
    for (int i = 0; i < nodeCnt; ++i)
        nodes[i].edges = -1;
    for (int i = 0; i < K; ++i)
        add(sBuilding[i], eBuilding[i], mDistance[i]);
    return;
}

void add(int sBuilding, int eBuilding, int mDistance)
{
    edgePool[edgeCnt].to = eBuilding;
    edgePool[edgeCnt].dist = mDistance;
    edgePool[edgeCnt].nxtEdge = nodes[sBuilding].edges;
    nodes[sBuilding].edges = edgeCnt++;

    edgePool[edgeCnt].to = sBuilding;
    edgePool[edgeCnt].dist = mDistance;
    edgePool[edgeCnt].nxtEdge = nodes[eBuilding].edges;
    nodes[eBuilding].edges = edgeCnt++;

    return;
}

// ===================================================================
// custom dijkstra
// ===================================================================

struct heapNode
{
    int id;
    int dist;
    Where from;
} heap[20001];
int heapSize;
int heapPos[10001][WHERE_SIZE];

inline void heapInit()
{
    for (int i = 1; i <= heapSize; ++i)
        heapPos[heap[i].id][heap[i].from] = 0;
    heapSize = 0;
    calcCnt++;
}

inline void siftUp(int cur)
{
    while (cur > 1)
    {
        int parent = cur >> 1;
        if (heap[cur].dist >= heap[parent].dist)
            break;
        std::swap(heap[cur], heap[parent]);
        std::swap(heapPos[heap[cur].id][heap[cur].from], heapPos[heap[parent].id][heap[parent].from]);
        cur = parent;
    }
}

inline void siftDown(int cur)
{
    while ((cur << 1) <= heapSize)
    {
        int child = cur << 1;
        if (heapSize >= (child | 1) && heap[child].dist > heap[child | 1].dist)
            child |= 1;
        if (heap[cur].dist <= heap[child].dist)
            break;
        std::swap(heap[cur], heap[child]);
        std::swap(heapPos[heap[cur].id][heap[cur].from], heapPos[heap[child].id][heap[child].from]);
        cur = child;
    }
}

inline void pushOrUpdate(heapNode node)
{
    // 새로운 id 이거나, 기존 id에 dist가 작아질 때에만 실행할 거임
    if (heapPos[node.id][node.from])
    {
        heap[heapPos[node.id][node.from]].dist = node.dist;
        siftUp(heapPos[node.id][node.from]);
        return;
    }
    heap[++heapSize] = node;
    heapPos[node.id][node.from] = heapSize;
    siftUp(heapSize);
}

inline heapNode pop()
{
    heapNode ret = heap[1];
    heapPos[ret.id][ret.from] = 0;
    if (heapSize > 1)
    {
        heap[1] = heap[heapSize--];
        heapPos[heap[1].id][heap[1].from] = 1;
        siftDown(1);
    }
    else
        heapSize = 0;
    return ret;
}

// ===================================================================

int calculate(int M, int mCoffee[], int P, int mBakery[], int R)
{
    int result = MAX_DIST;
    heapInit();
    for (int i = 0; i < M; ++i)
    {
        pushOrUpdate({mCoffee[i], 0, COFFEE});
        nodes[mCoffee[i]].dist[COFFEE] = 0;
        nodes[mCoffee[i]].calcCnt[COFFEE] = calcCnt;
    }
    for (int i = 0; i < P; ++i)
    {
        pushOrUpdate({mBakery[i], 0, BAKERY});
        nodes[mBakery[i]].dist[BAKERY] = 0;
        nodes[mBakery[i]].calcCnt[BAKERY] = calcCnt;
    }
    while (heapSize > 0)
    {
        heapNode cur = pop();
        if (cur.dist >= result)
            break;
        if (nodes[cur.id].calcCnt[cur.from] == calcCnt &&
            nodes[cur.id].calcCnt[cur.from ^ 1] == calcCnt &&
            nodes[cur.id].dist[cur.from] != 0 &&
            nodes[cur.id].dist[cur.from ^ 1] != 0)
        {
            result = std::min(result, nodes[cur.id].dist[cur.from] + nodes[cur.id].dist[cur.from ^ 1]);
        }
        for (int edgeIdx = nodes[cur.id].edges; edgeIdx != -1; edgeIdx = edgePool[edgeIdx].nxtEdge)
        {
            const Edge &edge = edgePool[edgeIdx];
            heapNode nxt = {edge.to, cur.dist + edge.dist, cur.from};
            if (nxt.dist > R || nxt.dist >= result)
                continue;
            if (nodes[nxt.id].calcCnt[nxt.from] == calcCnt && nodes[nxt.id].dist[nxt.from] <= nxt.dist)
                continue;
            pushOrUpdate(nxt);
            nodes[nxt.id].dist[nxt.from] = nxt.dist;
            nodes[nxt.id].calcCnt[nxt.from] = calcCnt;
        }
    }

    return result == MAX_DIST ? -1 : result;
}
