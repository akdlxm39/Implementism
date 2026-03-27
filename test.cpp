#include <algorithm>
#include <cstring>
#include <utility>

#define MAX_N 5005
#define MAX_EDGES 25005
#define HASH_SIZE 50021
#define INF 2100000000

// ==========================================
// Graph Structures
// ==========================================
struct Edge
{
    int id;
    int to;
    int dist;
    int next;
    bool isActive;
} edges[MAX_EDGES];

struct REdge
{
    int edgeIdx; // 매핑된 정방향 간선의 인덱스
    int from;
    int next;
} rEdges[MAX_EDGES];

struct HashNode
{
    int id;
    int edgeIdx;
    int next;
} hashTable[MAX_EDGES];

int head[MAX_N], rHead[MAX_N], hashHead[HASH_SIZE];
int dist[MAX_N], maxLen[MAX_N], parentEdge[MAX_N];
int edgeCnt, hashCnt;
int n, capital;
bool isInit;

// ==========================================
// Custom Heap
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
} heap[MAX_EDGES * 2];
int heapSize;

inline void heapInit()
{
    heapSize = 0;
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
// Core Logic
// ==========================================
void dijkstra_loop()
{
    while (heapSize > 0)
    {
        HeapNode cur = pop();

        if (dist[cur.id] < cur.dist || (dist[cur.id] == cur.dist && maxLen[cur.id] < cur.maxLen))
            continue;

        for (int e = head[cur.id]; e != -1; e = edges[e].next)
        {
            if (!edges[e].isActive)
                continue;

            int nxt = edges[e].to;
            int nxtDist = cur.dist + edges[e].dist;
            int nxtMaxLen = std::max(cur.maxLen, edges[e].dist);

            if (dist[nxt] > nxtDist || (dist[nxt] == nxtDist && maxLen[nxt] > nxtMaxLen))
            {
                dist[nxt] = nxtDist;
                maxLen[nxt] = nxtMaxLen;
                parentEdge[nxt] = edges[e].id;
                push({nxt, nxtDist, nxtMaxLen});
            }
        }
    }
}

// ==========================================
// API Functions
// ==========================================
void add(int mId, int sCity, int eCity, int mDistance);

void init(int N, int mCapital, int K, int mId[], int sCity[], int eCity[], int mDistance[])
{
    n = N;
    capital = mCapital;
    edgeCnt = 0;
    hashCnt = 0;
    isInit = true;

    for (int i = 0; i < HASH_SIZE; ++i)
        hashHead[i] = -1;

    // N의 제한은 5,000입니다[cite: 89].
    for (int i = 0; i < n; ++i)
    {
        head[i] = -1;
        rHead[i] = -1;
        dist[i] = INF;
        maxLen[i] = INF;
        parentEdge[i] = -1;
    }

    for (int i = 0; i < K; ++i)
    {
        add(mId[i], sCity[i], eCity[i], mDistance[i]);
    }

    isInit = false;
    dist[capital] = 0;
    maxLen[capital] = 0;

    heapInit();
    push({capital, 0, 0});
    dijkstra_loop();
}

void add(int mId, int sCity, int eCity, int mDistance)
{
    int currentEdgeIdx = edgeCnt;

    // 정방향 간선 연결
    edges[currentEdgeIdx] = {mId, eCity, mDistance, head[sCity], true};
    head[sCity] = currentEdgeIdx;

    // 역방향 간선 연결 (정방향 인덱스 직접 저장)
    rEdges[currentEdgeIdx] = {currentEdgeIdx, sCity, rHead[eCity]};
    rHead[eCity] = currentEdgeIdx;

    // Hash 체이닝 매핑
    int h = mId % HASH_SIZE;
    hashTable[hashCnt] = {mId, currentEdgeIdx, hashHead[h]};
    hashHead[h] = hashCnt++;

    edgeCnt++;

    if (isInit)
        return; // init 중에는 개별 다익스트라 방지

    if (dist[sCity] != INF)
    {
        int nxtDist = dist[sCity] + mDistance;
        int nxtMaxLen = std::max(maxLen[sCity], mDistance);

        if (dist[eCity] > nxtDist || (dist[eCity] == nxtDist && maxLen[eCity] > nxtMaxLen))
        {
            dist[eCity] = nxtDist;
            maxLen[eCity] = nxtMaxLen;
            parentEdge[eCity] = mId;

            heapInit();
            push({eCity, nxtDist, nxtMaxLen});
            dijkstra_loop();
        }
    }
}

void remove(int mId)
{
    int eIdx = -1;
    int h = mId % HASH_SIZE;

    for (int p = hashHead[h]; p != -1; p = hashTable[p].next)
    {
        if (hashTable[p].id == mId)
        {
            eIdx = hashTable[p].edgeIdx;
            break;
        }
    }

    if (eIdx == -1)
        return;
    edges[eIdx].isActive = false;
    int to = edges[eIdx].to;

    // 삭제된 간선이 최단경로에 사용되지 않았다면 무시
    if (parentEdge[to] != mId)
        return;

    // 1. 하위 서브트리 무효화
    int q[MAX_N];
    int front = 0, rear = 0;
    int invalidated[MAX_N];
    int invCnt = 0;

    q[rear++] = to;
    dist[to] = INF;
    maxLen[to] = INF;
    parentEdge[to] = -1;

    while (front < rear)
    {
        int cur = q[front++];
        invalidated[invCnt++] = cur;
        for (int e = head[cur]; e != -1; e = edges[e].next)
        {
            if (!edges[e].isActive)
                continue;
            int nxt = edges[e].to;
            if (parentEdge[nxt] == edges[e].id)
            {
                dist[nxt] = INF;
                maxLen[nxt] = INF;
                parentEdge[nxt] = -1;
                q[rear++] = nxt;
            }
        }
    }

    // 2. 역방향 간선을 통한 경계 복구
    heapInit();
    for (int i = 0; i < invCnt; ++i)
    {
        int cur = invalidated[i];
        for (int re = rHead[cur]; re != -1; re = rEdges[re].next)
        {
            int from = rEdges[re].from;
            int fwdIdx = rEdges[re].edgeIdx;

            if (!edges[fwdIdx].isActive)
                continue;

            if (dist[from] != INF)
            {
                int nxtDist = dist[from] + edges[fwdIdx].dist;
                int nxtMaxLen = std::max(maxLen[from], edges[fwdIdx].dist);

                if (dist[cur] > nxtDist || (dist[cur] == nxtDist && maxLen[cur] > nxtMaxLen))
                {
                    dist[cur] = nxtDist;
                    maxLen[cur] = nxtMaxLen;
                    parentEdge[cur] = edges[fwdIdx].id;
                    push({cur, nxtDist, nxtMaxLen});
                }
            }
        }
    }

    dijkstra_loop();
}

int calculate(int mCity)
{
    if (dist[mCity] == INF)
        return -1;
    return maxLen[mCity];
}