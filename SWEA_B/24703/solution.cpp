#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>

#define MAX_WIDTH 500
using namespace std;

struct Result
{
    int ID;
    int height;
    int used;
};

struct Tank
{
    int ID;
    vector<int> lengths, up_shapes;
    Tank(int mId, int mLength[MAX_WIDTH], int mUpShapes[MAX_WIDTH], int w) : ID(mId)
    {
        lengths.assign(mLength, mLength + w);
        up_shapes.assign(mUpShapes, mUpShapes + w);
    }
    bool operator<(const Tank &other) const
    {
        return ID < other.ID;
    }
};

int tanks_cnt, width, height;
vector<Tank> tanks;
vector<int> tmp_lengths;
unordered_set<int> candidate[1000];

void init(int N, int mWidth, int mHeight, int mIDs[], int mLengths[][MAX_WIDTH], int mUpShapes[][MAX_WIDTH])
{
    tanks_cnt = N;
    width = mWidth;
    height = mHeight;
    tanks.clear();
    tanks.reserve(N);
    for (int i = 0; i < tanks_cnt; ++i)
        tanks.emplace_back(mIDs[i], mLengths[i], mUpShapes[i], width);
    sort(tanks.begin(), tanks.end());
    for (int i = 0; i < tanks_cnt; ++i)
    {
        const Tank &tank = tanks[i];
        int idx = tank.up_shapes[0] * 4 + tank.up_shapes[1];
        for (int j = 2; j < width; ++j)
        {
            idx %= 16;
            idx *= 4;
            idx += tank.up_shapes[j];
            candidate[idx].insert(i * 1000 + j - 2);
        }
    }
}

int checkStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{
    int ret = 0;
    int idx = mDownShapes[0] * 16 + mDownShapes[1] * 4 + mDownShapes[2];
    for (auto iter = candidate[idx].begin(); iter != candidate[idx].end(); ++iter)
    {
        const Tank &tank = tanks[(*iter) / 1000];
        int i = (*iter) % 1000;
        int flag = 1;
        for (int j = 0; j < 3; ++j)
        {
            if (j != 0)
            {
                int gap = tank.lengths[i + j - 1] - tank.lengths[i + j];
                if (gap > 0 && gap >= mLengths[j])
                {
                    flag = 0;
                    break;
                }
                else if (gap < 0 && -gap >= mLengths[j - 1])
                {
                    flag = 0;
                    break;
                }
            }
            if (tank.lengths[i + j] + mLengths[j] > height)
            {
                flag = 0;
                break;
            }
        }
        ret += flag;
    }
    return ret;
}

int addStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{
    int idx = mDownShapes[0] * 16 + mDownShapes[1] * 4 + mDownShapes[2];
    int ti = -1, wi = -1;
    for (auto iter = candidate[idx].begin(); iter != candidate[idx].end(); ++iter)
    {
        const Tank &tank = tanks[(*iter) / 1000];
        int i = (*iter) % 1000;
        bool flag = true;
        for (int j = 0; j < 3; ++j)
        {
            if (j != 0)
            {
                int gap = tank.lengths[i + j - 1] - tank.lengths[i + j];
                if (gap > 0 && gap >= mLengths[j])
                {
                    flag = false;
                    break;
                }
                else if (gap < 0 && -gap >= mLengths[j - 1])
                {
                    flag = false;
                    break;
                }
            }
            if (tank.lengths[i + j] + mLengths[j] > height)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            if (ti == -1 || tanks[ti].ID > tank.ID)
            {
                ti = (*iter) / 1000;
                wi = i;
            }
            else if (tanks[ti].ID == tank.ID && wi > i)
                wi = i;
        }
    }
    if (ti == -1)
        return 0;
    Tank &tank = tanks[ti];
    if (0 <= wi - 2)
    {
        int prev = tank.up_shapes[wi - 2] * 16 + tank.up_shapes[wi - 1] * 4 + tank.up_shapes[wi];
        int nxt = tank.up_shapes[wi - 2] * 16 + tank.up_shapes[wi - 1] * 4 + mUpShapes[0];
        candidate[prev].erase(ti * 1000 + wi - 2);
        candidate[nxt].insert(ti * 1000 + wi - 2);
    }
    if (0 <= wi - 1 && wi + 1 < width)
    {
        int prev = tank.up_shapes[wi - 1] * 16 + tank.up_shapes[wi] * 4 + tank.up_shapes[wi + 1];
        int nxt = tank.up_shapes[wi - 1] * 16 + mUpShapes[0] * 4 + mUpShapes[1];
        candidate[prev].erase(ti * 1000 + wi - 1);
        candidate[nxt].insert(ti * 1000 + wi - 1);
    }
    if (wi + 2 < width)
    {
        int prev = tank.up_shapes[wi] * 16 + tank.up_shapes[wi + 1] * 4 + tank.up_shapes[wi + 2];
        int nxt = mUpShapes[0] * 16 + mUpShapes[1] * 4 + mUpShapes[2];
        candidate[prev].erase(ti * 1000 + wi);
        candidate[nxt].insert(ti * 1000 + wi);
    }
    if (wi + 3 < width)
    {
        int prev = tank.up_shapes[wi + 1] * 16 + tank.up_shapes[wi + 2] * 4 + tank.up_shapes[wi + 3];
        int nxt = mUpShapes[1] * 16 + mUpShapes[2] * 4 + tank.up_shapes[wi + 3];
        candidate[prev].erase(ti * 1000 + wi + 1);
        candidate[nxt].insert(ti * 1000 + wi + 1);
    }
    if (wi + 4 < width)
    {
        int prev = tank.up_shapes[wi + 2] * 16 + tank.up_shapes[wi + 3] * 4 + tank.up_shapes[wi + 4];
        int nxt = mUpShapes[2] * 16 + tank.up_shapes[wi + 3] * 4 + tank.up_shapes[wi + 4];
        candidate[prev].erase(ti * 1000 + wi + 2);
        candidate[nxt].insert(ti * 1000 + wi + 2);
    }
    for (int j = 0; j < 3; ++j)
    {
        tank.lengths[wi + j] += mLengths[j];
        tank.up_shapes[wi + j] = mUpShapes[j];
    }
    return tank.ID * 1000 + wi + 1;
}

Result pourIn(int mWater)
{
    Result ret = Result{0, 0, 0};
    for (const Tank &tank : tanks)
    {
        tmp_lengths.assign(tank.lengths.begin(), tank.lengths.end());
        sort(tmp_lengths.begin(), tmp_lengths.end());
        int len = 0, w = 0, used = 0;
        for (int l : tmp_lengths)
        {
            if (mWater < used + (l - len) * w)
            {
                int can_l = (mWater - used) / w;
                used += can_l * w;
                len += can_l;
                break;
            }
            used += (l - len) * w;
            len = l;
            w++;
        }
        if (w == width)
        {
            int can_l = min(height - len, (mWater - used) / width);
            len += can_l;
            used += can_l * width;
        }
        if (used == 0)
            continue;
        if (ret.height < len)
        {
            ret.ID = tank.ID;
            ret.height = len;
            ret.used = used;
        }
        else if (ret.height == len && ret.used < used)
        {
            ret.ID = tank.ID;
            ret.used = used;
        }
    }
    return ret;
}
