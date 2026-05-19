#include <algorithm>
#include <cstring>
#include <utility>

#define HASH_SIZE 50021

// id, from, to, dist, isActive, nxtEdge, nxtHash
struct Edge
{
    int id;
    int from;
    int to;
    int dist;
    int isActive;
    int nxtEdge;
    int nxtHash;
} edgePool[24007];
int edgeCnt;
int edgeHash[HASH_SIZE];

struct Node
{
    int edges;
    int dist;
    int maxLen;
    int calcCnt;
} nodes[5001];
int n;
int capital;
int calcCnt;
bool isDirty;

void add(int mId, int sCity, int eCity, int mDistance);

void init(int N, int mCapital, int K, int mId[], int sCity[], int eCity[], int mDistance[])
{
    edgeCnt = 0;
    n = N;
    capital = mCapital;
    memset(edgeHash, -1, sizeof(edgeHash));
    for (int i = 0; i < N; ++i)
        nodes[i].edges = -1;
    isDirty = true;
    for (int i = 0; i < K; ++i)
        add(mId[i], sCity[i], eCity[i], mDistance[i]);
    return;
}

// ==========================================
// custom heap
// ==========================================
struct HeapNode
{
    int id;
    int dist;
    int maxLen;
    bool operator<(const HeapNode &other) const
    {
        if (dist == other.dist)
            return maxLen < other.maxLen;
        return dist < other.dist;
    }
} heap[25001];
int heapSize;

inline void heapInit()
{
    heapSize = 0;
    calcCnt++;
}

inline void siftUp(int cur)
{
    while (cur > 1)
    {
        int par = cur >> 1;
        if (heap[cur] < heap[par])
        {
            std::swap(heap[cur], heap[par]);
            cur = par;
        }
        else
            break;
    }
}

inline void siftDown(int cur)
{
    while ((cur << 1) <= heapSize)
    {
        int child = cur << 1;
        if ((child | 1) <= heapSize && heap[child | 1] < heap[child])
            child |= 1;
        if (heap[child] < heap[cur])
        {
            std::swap(heap[cur], heap[child]);
            cur = child;
        }
        else
            break;
    }
}

inline void push(HeapNode node)
{
    heap[++heapSize] = node;
    siftUp(heapSize);
}

inline HeapNode pop()
{
    HeapNode ret = heap[1];
    if (heapSize > 1)
    {
        heap[1] = heap[heapSize--];
        siftDown(1);
    }
    else
        heapSize = 0;
    return ret;
}

// ==========================================

void dijkstra_loop()
{
    while (heapSize > 0)
    {
        HeapNode cur = pop();
        if (nodes[cur.id].dist < cur.dist || nodes[cur.id].maxLen < cur.maxLen)
            continue;
        for (int edgeIdx = nodes[cur.id].edges; edgeIdx != -1; edgeIdx = edgePool[edgeIdx].nxtEdge)
        {
            if (!edgePool[edgeIdx].isActive)
                continue;
            HeapNode nxt = {edgePool[edgeIdx].to, cur.dist + edgePool[edgeIdx].dist,
                            std::max(cur.maxLen, edgePool[edgeIdx].dist)};
            if (nodes[nxt.id].calcCnt == calcCnt &&
                (nodes[nxt.id].dist < nxt.dist ||
                 (nodes[nxt.id].dist == nxt.dist && nodes[nxt.id].maxLen <= nxt.maxLen)))
                continue;
            push(nxt);
            nodes[nxt.id].dist = nxt.dist;
            nodes[nxt.id].maxLen = nxt.maxLen;
            nodes[nxt.id].calcCnt = calcCnt;
        }
    }
}

void dijkstra()
{
    heapInit();
    push({capital, 0, 0});
    nodes[capital].dist = 0;
    nodes[capital].maxLen = 0;
    nodes[capital].calcCnt = calcCnt;
    dijkstra_loop();
}

void add(int mId, int sCity, int eCity, int mDistance)
{
    edgePool[edgeCnt].id = mId;
    edgePool[edgeCnt].from = sCity;
    edgePool[edgeCnt].to = eCity;
    edgePool[edgeCnt].dist = mDistance;
    edgePool[edgeCnt].isActive = true;
    edgePool[edgeCnt].nxtEdge = nodes[sCity].edges;
    nodes[sCity].edges = edgeCnt;
    edgePool[edgeCnt].nxtHash = edgeHash[mId % HASH_SIZE];
    edgeHash[mId % HASH_SIZE] = edgeCnt;
    edgeCnt++;

    if (isDirty)
        return;
    if (nodes[sCity].calcCnt == calcCnt)
    {
        HeapNode nxt = {eCity, nodes[sCity].dist + mDistance, std::max(nodes[sCity].maxLen, mDistance)};
        if (nodes[nxt.id].calcCnt == calcCnt &&
            (nodes[nxt.id].dist < nxt.dist || (nodes[nxt.id].dist == nxt.dist && nodes[nxt.id].maxLen <= nxt.maxLen)))
            return;
        push(nxt);
        nodes[nxt.id].dist = nxt.dist;
        nodes[nxt.id].maxLen = nxt.maxLen;
        nodes[nxt.id].calcCnt = calcCnt;
        dijkstra_loop();
    }
    if (nodes[sCity].calcCnt == calcCnt)
    {
        int nxtDist = nodes[sCity].dist + mDistance;
        int nxtMaxLen = std::max(nodes[sCity].maxLen, mDistance);
        if (nodes[eCity].calcCnt != calcCnt || nxtDist < nodes[eCity].dist ||
            (nxtDist == nodes[eCity].dist && nxtMaxLen < nodes[eCity].maxLen))
        {
            nodes[eCity].dist = nxtDist;
            nodes[eCity].maxLen = nxtMaxLen;
            nodes[eCity].calcCnt = calcCnt;
            push({eCity, nxtDist, nxtMaxLen});
            dijkstra_loop();
        }
    }
    return;
}

void remove(int mId)
{
    int edgeIdx = edgeHash[mId % HASH_SIZE];
    int to, from, dist;
    while (edgeIdx != -1)
    {
        if (edgePool[edgeIdx].id == mId)
        {
            edgePool[edgeIdx].isActive = false;
            from = edgePool[edgeIdx].from;
            to = edgePool[edgeIdx].to;
            dist = edgePool[edgeIdx].dist;
            break;
        }
        edgeIdx = edgePool[edgeIdx].nxtHash;
    }
    if (edgeIdx == -1 || isDirty)
        return;
    if (nodes[to].calcCnt != calcCnt || nodes[from].calcCnt != calcCnt)
        return;
    if (nodes[to].dist < nodes[from].dist + dist ||
        (nodes[to].dist == nodes[from].dist + dist && nodes[to].maxLen < dist))
        return;
    isDirty = true;
    return;
}

int calculate(int mCity)
{
    if (isDirty)
    {
        dijkstra();
        isDirty = false;
    }
    if (nodes[mCity].calcCnt != calcCnt)
        return -1;
    return nodes[mCity].maxLen;
}