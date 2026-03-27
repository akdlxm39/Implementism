const int INF = 1e9;

int n, growthTime[3];
int grid[1001][1001];

struct Crop
{
    int y, x;
    int sTime;
    int category;
    int water;
    bool isActive;
} cropPool[100'001];
int nxtCrop[100'001];
int cropCnt;

struct Block
{
    int crops;
    int activeCnt;
    int water;
    int min[3][30];
} blocks[32][32];

void rebuild(int by, int bx)
{
    Block &block = blocks[by][bx];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 30; ++j)
            block.min[i][j] = INF;
    int cur = block.crops;
    int prev = 0;
    while (cur)
    {
        if (!cropPool[cur].isActive)
        {
            if (prev == 0)
                block.crops = nxtCrop[cur];
            else
                nxtCrop[prev] = nxtCrop[cur];
        }
        else
        {
            int c = cropPool[cur].category;
            int g = growthTime[c];
            int q = cropPool[cur].sTime / g;
            int r = cropPool[cur].sTime % g;
            int val = -q + cropPool[cur].water;
            if (block.min[c][r] > val)
                block.min[c][r] = val;
            prev = cur;
        }
        cur = nxtCrop[cur];
    }
}

void init(int N, int mGrowthTime[])
{
    n = N;
    for (int i = 0; i < 3; ++i)
        growthTime[i] = mGrowthTime[i];

    cropCnt = 1;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            grid[i][j] = 0;

    int maxB = N >> 5;
    for (int i = 0; i <= maxB; ++i)
    {
        for (int j = 0; j <= maxB; ++j)
        {
            Block &block = blocks[i][j];
            block.crops = 0;
            block.activeCnt = 0;
            block.water = 0;
            for (int k = 0; k < 3; ++k)
                for (int l = 0; l < 30; ++l)
                    block.min[k][l] = INF;
        }
    }
}

int sow(int mTime, int mRow, int mCol, int mCategory)
{
    if (grid[mRow][mCol])
        return 0;
    int id = cropCnt++;
    Block &block = blocks[mRow >> 5][mCol >> 5];

    cropPool[id] = {mRow, mCol, mTime, mCategory, -block.water, true};
    grid[mRow][mCol] = id;
    nxtCrop[id] = block.crops;
    block.crops = id;
    block.activeCnt++;

    int g = growthTime[mCategory];
    int q = mTime / g;
    int r = mTime % g;
    int val = -q + cropPool[id].water;
    if (block.min[mCategory][r] > val)
        block.min[mCategory][r] = val;
    return 1;
}

int water(int mTime, int G, int mRow, int mCol, int mHeight, int mWidth)
{
    int y1 = mRow, y2 = mRow + mHeight - 1;
    int x1 = mCol, x2 = mCol + mWidth - 1;
    int by1 = y1 >> 5, by2 = y2 >> 5;
    int bx1 = x1 >> 5, bx2 = x2 >> 5;
    int ret = 0;
    for (int by = by1; by <= by2; ++by)
    {
        for (int bx = bx1; bx <= bx2; ++bx)
        {
            bool fullY = (y1 <= by * 32) && (by * 32 + 31 <= y2);
            bool fullX = (x1 <= bx * 32) && (bx * 32 + 31 <= x2);
            if (fullY && fullX)
            {
                blocks[by][bx].water += G;
                ret += blocks[by][bx].activeCnt;
            }
            else
            {
                bool updated = false;
                int cur = blocks[by][bx].crops;
                while (cur)
                {
                    if (cropPool[cur].isActive)
                    {
                        int cy = cropPool[cur].y, cx = cropPool[cur].x;
                        if (y1 <= cy && cy <= y2 && x1 <= cx && cx <= x2)
                        {
                            cropPool[cur].water += G;
                            ret++;
                            updated = true;
                        }
                    }
                    cur = nxtCrop[cur];
                }
                if (updated)
                    rebuild(by, bx);
            }
        }
    }
    return ret;
}

int harvest(int mTime, int L, int mRow, int mCol, int mHeight, int mWidth)
{
    int y1 = mRow, y2 = mRow + mHeight - 1;
    int x1 = mCol, x2 = mCol + mWidth - 1;
    int by1 = y1 >> 5, by2 = y2 >> 5;
    int bx1 = x1 >> 5, bx2 = x2 >> 5;
    for (int by = by1; by <= by2; ++by)
    {
        for (int bx = bx1; bx <= bx2; ++bx)
        {
            if (blocks[by][bx].activeCnt == 0)
                continue;
            bool fullY = (y1 <= by * 32) && (by * 32 + 31 <= y2);
            bool fullX = (x1 <= bx * 32) && (bx * 32 + 31 <= x2);
            if (fullY && fullX)
            {
                for (int c = 0; c < 3; ++c)
                {
                    int g = growthTime[c];
                    int q = mTime / g;
                    int r = mTime % g;
                    for (int rp = 0; rp < g; ++rp)
                        if (q + blocks[by][bx].min[c][rp] + blocks[by][bx].water - (r < rp) < L)
                            return 0;
                }
            }
            else
            {
                int cur = blocks[by][bx].crops;
                while (cur)
                {
                    if (cropPool[cur].isActive)
                    {
                        int cy = cropPool[cur].y, cx = cropPool[cur].x;
                        if (y1 <= cy && cy <= y2 && x1 <= cx && cx <= x2)
                        {
                            int c = cropPool[cur].category;
                            int g = growthTime[c];
                            if ((mTime - cropPool[cur].sTime) / g + cropPool[cur].water + blocks[by][bx].water < L)
                                return 0;
                        }
                    }
                    cur = nxtCrop[cur];
                }
            }
        }
    }

    int ret = 0;
    for (int by = by1; by <= by2; ++by)
    {
        for (int bx = bx1; bx <= bx2; ++bx)
        {
            if (blocks[by][bx].activeCnt == 0)
                continue;
            bool fullY = (y1 <= by * 32) && (by * 32 + 31 <= y2);
            bool fullX = (x1 <= bx * 32) && (bx * 32 + 31 <= x2);
            if (fullY && fullX)
            {
                ret += blocks[by][bx].activeCnt;
                int cur = blocks[by][bx].crops;
                while (cur)
                {
                    if (cropPool[cur].isActive)
                    {
                        grid[cropPool[cur].y][cropPool[cur].x] = 0;
                        cropPool[cur].isActive = false;
                    }
                    cur = nxtCrop[cur];
                }
                blocks[by][bx].activeCnt = 0;
                rebuild(by, bx);
            }
            else
            {
                bool updated = false;
                int cur = blocks[by][bx].crops;
                while (cur)
                {
                    if (cropPool[cur].isActive)
                    {
                        int cy = cropPool[cur].y, cx = cropPool[cur].x;
                        if (y1 <= cy && cy <= y2 && x1 <= cx && cx <= x2)
                        {
                            grid[cy][cx] = 0;
                            cropPool[cur].isActive = false;
                            ret++;
                            blocks[by][bx].activeCnt--;
                            updated = true;
                        }
                    }
                    cur = nxtCrop[cur];
                }
                if (updated)
                    rebuild(by, bx);
            }
        }
    }
    return ret;
}