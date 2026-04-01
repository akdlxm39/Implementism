#include <iostream>

using namespace std;

typedef long long ll;

struct Node
{
    int leftChild;
    int rightChild;
    ll sum;
} nodePool[10'000'000];
int nodeCnt;

int addNode()
{
    int id = nodeCnt++;
    nodePool[id].leftChild = -1;
    nodePool[id].rightChild = -1;
    nodePool[id].sum = 0;
    return id;
}

int treeRoot[6];

void update(int node, int left, int right, int idx, ll num)
{
    nodePool[node].sum += num;
    if (left == right)
        return;
    int mid = left + (right - left) / 2;
    if (left <= idx && idx <= mid)
    {
        if (nodePool[node].leftChild == -1)
            nodePool[node].leftChild = addNode();
        update(nodePool[node].leftChild, left, mid, idx, num);
    }
    else
    {
        if (nodePool[node].rightChild == -1)
            nodePool[node].rightChild = addNode();
        update(nodePool[node].rightChild, mid + 1, right, idx, num);
    }
}

ll query(int node, int left, int right, int start, int end)
{
    if (end < left || right < start)
        return 0;
    if (start <= left && right <= end)
        return nodePool[node].sum;
    int mid = left + (right - left) / 2;
    ll ret = 0;
    if (nodePool[node].leftChild != -1)
        ret += query(nodePool[node].leftChild, left, mid, start, end);
    if (nodePool[node].rightChild != -1)
        ret += query(nodePool[node].rightChild, mid + 1, right, start, end);
    return ret;
}

int main()
{
    return 0;
}