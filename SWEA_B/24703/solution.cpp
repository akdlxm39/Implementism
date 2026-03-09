#include <algorithm>
#include <iostream>
#include <vector>

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
    // cout << "init\n";
}

int checkStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{
    int ret = 0;
    for (const Tank &tank : tanks)
    {
        for (int i = 0; i < width - 2; ++i)
        {
            int flag = 1;
            for (int j = 0; j < 3; ++j)
            {
                if (tank.up_shapes[i + j] != mDownShapes[j])
                {
                    flag = 0;
                    break;
                }
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
    }
    // cout << "check : " << ret << '\n';
    return ret;
}

int addStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{
    for (Tank &tank : tanks)
    {
        for (int i = 0; i < width - 2; ++i)
        {
            bool flag = true;
            for (int j = 0; j < 3; ++j)
            {
                if (tank.up_shapes[i + j] != mDownShapes[j])
                {
                    flag = false;
                    break;
                }
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
                for (int j = 0; j < 3; ++j)
                {
                    tank.lengths[i + j] += mLengths[j];
                    tank.up_shapes[i + j] = mUpShapes[j];
                }
                // cout << "add : " << tank.ID * 1000 + i + 1 << '\n';
                return tank.ID * 1000 + i + 1;
            }
        }
    }
    // cout << "add : 0 \n";
    return 0;
}

Result pourIn(int mWater)
{
    Result ret = Result{0, 0, 0};
    for (const Tank &tank : tanks)
    {
        tmp_lengths.assign(tank.lengths.begin(), tank.lengths.end());
        sort(tmp_lengths.begin(), tmp_lengths.end());
        // cout << "check len : ";
        // for (int l : tmp_lengths)
        //     cout << l << ' ';
        // cout << '\n';
        int len = 0, w = 0, used = 0;
        for (int l : tmp_lengths)
        {
            if (mWater < used + (l - len) * w)
            {
                // cout << "break : " << used << ' ' << l << ' ' << w << '\n';
                int can_l = (mWater - used) / w;
                // cout << "break : " << can_l << '\n';
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
        // cout << "check : " << tank.ID << ' ' << len << ' ' << w << ' ' << used << '\n';
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
    // cout << "pour : " << ret.ID << ' ' << ret.height << ' ' << ret.used << '\n';
    return ret;
}
