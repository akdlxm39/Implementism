#include <queue>
#include <deque>
#include <vector>
#include <cstring>

#define MAXL (10)
#define uint unsigned int

struct Keyword
{
    int key;
    int cnt;
    int groupCnt;
    int prevHash;
    int nxtHash;
    int topCnt;
    int topParent;
    int len;
    char word[MAXL + 1];
    bool operator<(const Keyword &other) const
    {
        if (cnt != other.cnt)
            return cnt < other.cnt;
        return strcmp(word, other.word) > 0;
    }
} wordPool[10007];
int wordCnt;
int wordHash[20011];
int topCnt = 0;
int n;
std::deque<int> dq;

uint getHash(char mKeyword[])
{
    uint key = 5381;
    int c;
    while ((c = *mKeyword++))
    {
        key = ((key << 5) + key) + c;
    }
    return key % 20011;
}

int insert(char mKeyword[])
{
    int key = getHash(mKeyword);
    int wordIdx = wordHash[key];
    while (wordIdx != -1)
    {
        if (strcmp(wordPool[wordIdx].word, mKeyword) == 0)
        {
            wordPool[wordIdx].cnt++;
            return wordIdx;
        }
        wordIdx = wordPool[wordIdx].nxtHash;
    }

    Keyword &cur = wordPool[wordCnt];
    for (cur.len = 0; mKeyword[cur.len] != '\0'; ++cur.len)
        cur.word[cur.len] = mKeyword[cur.len];
    cur.word[cur.len] = '\0';
    cur.key = key;
    cur.cnt = 1;
    if (wordHash[key] != -1)
        wordPool[wordHash[key]].prevHash = wordCnt;
    cur.prevHash = -1;
    cur.nxtHash = wordHash[key];
    wordHash[key] = wordCnt;
    return wordCnt++;
}

void erase(int wordIdx)
{
    if (--wordPool[wordIdx].cnt > 0)
        return;
    if (wordPool[wordIdx].prevHash != -1)
        wordPool[wordPool[wordIdx].prevHash].nxtHash = wordPool[wordIdx].nxtHash;
    else
        wordHash[wordPool[wordIdx].key] = wordPool[wordIdx].nxtHash;
    if (wordPool[wordIdx].nxtHash != -1)
        wordPool[wordPool[wordIdx].nxtHash].prevHash = wordPool[wordIdx].prevHash;
}

void init(int N)
{
    n = N;
    wordCnt = 0;
    memset(wordHash, -1, sizeof(wordHash));
    dq.clear();
}

void addKeyword(char mKeyword[])
{
    dq.push_back(insert(mKeyword));
    if (dq.size() > n)
    {
        int delWordIdx = dq.front();
        dq.pop_front();
        erase(delWordIdx);
    }
}

int _find(int wordIdx)
{
    if (wordPool[wordIdx].topParent == wordIdx)
        return wordIdx;
    return wordPool[wordIdx].topParent = _find(wordPool[wordIdx].topParent);
}

int _union(int curIdx, int prevIdx)
{
    int pCurIdx = _find(curIdx);
    int pPrevIdx = _find(prevIdx);
    if (wordPool[pCurIdx] < wordPool[pPrevIdx])
    {
        wordPool[pCurIdx].topParent = pPrevIdx;
        wordPool[pPrevIdx].groupCnt += wordPool[pCurIdx].groupCnt;
        return pPrevIdx;
    }
    wordPool[pPrevIdx].topParent = pCurIdx;
    wordPool[pCurIdx].groupCnt += wordPool[pPrevIdx].groupCnt;
    return pCurIdx;
}

struct cmp
{
    bool operator()(int a, int b) const
    {
        Keyword &A = wordPool[a];
        Keyword &B = wordPool[b];
        if (A.groupCnt != B.groupCnt)
            return A.groupCnt > B.groupCnt;
        return strcmp(A.word, B.word) < 0;
    }
};

std::priority_queue<int, std::vector<int>, cmp> pq;

int top5Keyword(char mRet[][MAXL + 1])
{
    topCnt++;
    for (auto it = dq.begin(); it != dq.end(); ++it)
    {
        Keyword &cur = wordPool[*it];
        if (cur.topCnt == topCnt)
            continue;
        cur.topCnt = topCnt;
        cur.topParent = *it;
        cur.groupCnt = cur.cnt;
        for (auto it2 = dq.begin(); it2 != it; ++it2)
        {
            if (_find(*it) == _find(*it2))
                continue;
            Keyword &prev = wordPool[*it2];
            if (cur.len != prev.len)
                continue;
            int diff = 0;
            for (int i = 0; i < cur.len; ++i)
                diff += (cur.word[i] != prev.word[i]);
            if (diff != 1)
                continue;
            _union(*it, *it2);
        }
    }
    topCnt++;
    for (auto it = dq.begin(); it != dq.end(); ++it)
    {
        Keyword &cur = wordPool[*it];
        if (cur.topParent != *it)
            continue;
        if (cur.topCnt == topCnt)
            continue;
        cur.topCnt = topCnt;
        pq.push(*it);
        if (pq.size() > 5)
            pq.pop();
    }
    int ret = pq.size();
    for (int i = pq.size() - 1; i >= 0; --i)
    {
        for (int j = 0; j < wordPool[pq.top()].len; ++j)
            mRet[i][j] = wordPool[pq.top()].word[j];
        pq.pop();
    }
    return ret;
}