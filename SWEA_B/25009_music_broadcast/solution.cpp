#include <cstring>

#define HASH_SIZE 10007
#define MAX_SIZE 2'000'007

struct Worker
{
    int id;
    int start, end;
    int nxtHash;
} workerPool[5000];
int workerCnt;
int workerHash[HASH_SIZE];
int music;

// ========================================
// fenwick tree (range update + point query)
// ========================================

int tree[MAX_SIZE];

void update(int idx, int delta)
{
    while (idx < MAX_SIZE)
    {
        tree[idx] += delta;
        idx += idx & -idx;
    }
}

int query(int idx)
{
    int result = 0;
    while (idx > 0)
    {
        result += tree[idx];
        idx -= idx & -idx;
    }
    return result;
}

// ========================================

int addWorker(int mID, int mStart, int mEnd)
{
    workerPool[workerCnt].id = mID;
    workerPool[workerCnt].start = mStart;
    workerPool[workerCnt].end = mEnd;
    return workerCnt++;
}

void init(int musicTime)
{
    workerCnt = 0;
    memset(workerHash, -1, sizeof(workerHash));
    memset(tree, 0, sizeof(tree));
    music = musicTime;
}

void add(int mID, int mStart, int mEnd)
{
    mEnd -= music;
    int key = mID % HASH_SIZE;
    int curIdx = workerHash[key];
    while (curIdx != -1)
    {
        if (workerPool[curIdx].id == mID)
        {
            if (workerPool[curIdx].start != -1)
            {
                update(workerPool[curIdx].start, -1);
                update(workerPool[curIdx].end + 1, 1);
            }
            workerPool[curIdx].start = mStart;
            workerPool[curIdx].end = mEnd;
            update(workerPool[curIdx].start, 1);
            update(workerPool[curIdx].end + 1, -1);
            return;
        }
        curIdx = workerPool[curIdx].nxtHash;
    }
    int newIdx = addWorker(mID, mStart, mEnd);
    workerPool[newIdx].nxtHash = workerHash[key];
    workerHash[key] = newIdx;
    update(workerPool[newIdx].start, 1);
    update(workerPool[newIdx].end + 1, -1);
}

void remove(int mID)
{
    int key = mID % HASH_SIZE;
    int curIdx = workerHash[key];
    while (curIdx != -1)
    {
        if (workerPool[curIdx].id == mID)
        {
            if (workerPool[curIdx].start != -1)
            {
                update(workerPool[curIdx].start, -1);
                update(workerPool[curIdx].end + 1, 1);
                workerPool[curIdx].start = -1;
            }
            return;
        }
        curIdx = workerPool[curIdx].nxtHash;
    }
}

int getCnt(int mBSTime)
{
    return query(mBSTime);
}