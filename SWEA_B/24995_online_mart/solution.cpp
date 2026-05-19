#include <cstring>
#include <algorithm>
#include <set>
#include <queue>

#define MAX_ITEMS 50'007
#define HASH_SIZE 100'007

struct RESULT
{
    int cnt;
    int IDs[5];
};

struct Block
{
    int discount;
    std::set<std::pair<int, int>> rank;
} grid[6][6];

struct Item
{
    int id;
    int price;
    int nxtHash;
    Block *block;
    std::set<std::pair<int, int>>::iterator setIter;

} items[MAX_ITEMS];
int itemCnt;
int itemHash[HASH_SIZE];

int getIdx(int mID)
{
    int cur = itemHash[mID % HASH_SIZE];
    while (cur != -1 && items[cur].id != mID)
        cur = items[cur].nxtHash;
    return cur;
}

void init()
{
    itemCnt = 0;
    memset(itemHash, -1, sizeof(itemHash));
    for (int i = 1; i <= 5; ++i)
    {
        for (int j = 1; j <= 5; ++j)
        {
            grid[i][j].discount = 0;
            grid[i][j].rank.clear();
        }
    }
    return;
}

int sell(int mID, int mCategory, int mCompany, int mPrice)
{
    int key = mID % HASH_SIZE;
    Item &newItem = items[itemCnt];
    Block &curBlock = grid[mCategory][mCompany];
    newItem.id = mID;
    newItem.price = mPrice + curBlock.discount;
    newItem.nxtHash = itemHash[key];
    itemHash[key] = itemCnt;
    newItem.block = &curBlock;
    newItem.setIter = curBlock.rank.insert({newItem.price, newItem.id}).first;
    itemCnt++;
    return curBlock.rank.size();
}

int closeSale(int mID)
{
    int res = -1;
    int idx = getIdx(mID);
    if (idx != -1 && items[idx].block != nullptr)
    {
        res = items[idx].price - items[idx].block->discount;
        items[idx].block->rank.erase(items[idx].setIter);
        items[idx].block = nullptr;
    }
    return res;
}

int discount(int mCategory, int mCompany, int mAmount)
{
    Block &curBlock = grid[mCategory][mCompany];
    curBlock.discount += mAmount;
    auto it = curBlock.rank.begin();
    while (it != curBlock.rank.end() && it->first <= curBlock.discount)
    {
        items[getIdx(it->second)].block = nullptr;
        it = curBlock.rank.erase(it);
    }
    if (curBlock.discount > 1'000'000'000)
    {
        std::set<std::pair<int, int>> newRank;
        while (it != curBlock.rank.end())
        {
            Item &curItem = items[getIdx(it->second)];
            curItem.price -= curBlock.discount;
            curItem.setIter = newRank.insert({curItem.price, curItem.id}).first;
            ++it;
        }
        curBlock.rank.swap(newRank);
        curBlock.discount = 0;
    }
    return curBlock.rank.size();
}

void showBlock(Block &curBlock, std::priority_queue<std::pair<int, int>> &pq)
{
    auto it = curBlock.rank.begin();
    for (int i = 0; i < 5 && it != curBlock.rank.end(); ++i, ++it)
    {
        int price = it->first - curBlock.discount;
        if (price > pq.top().first)
            break;
        pq.push({price, it->second});
        if (pq.size() > 5)
            pq.pop();
    }
}

RESULT show(int mHow, int mCode)
{
    RESULT res;
    std::priority_queue<std::pair<int, int>> pq;
    pq.push({1'000'000'000, -1});
    if (mHow == 0)
    {
        for (int i = 1; i <= 5; ++i)
            for (int j = 1; j <= 5; ++j)
                showBlock(grid[i][j], pq);
    }
    else if (mHow == 1)
    {
        for (int i = 1; i <= 5; ++i)
            showBlock(grid[mCode][i], pq);
    }
    else if (mHow == 2)
    {
        for (int i = 1; i <= 5; ++i)
            showBlock(grid[i][mCode], pq);
    }
    if (pq.top().second == -1)
        pq.pop();
    res.cnt = pq.size();
    for (int i = res.cnt - 1; i >= 0; --i)
    {
        res.IDs[i] = pq.top().second;
        pq.pop();
    }

    return res;
}
