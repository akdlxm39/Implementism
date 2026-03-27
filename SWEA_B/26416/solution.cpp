const int INF = 1e9;

int n, growthTime[3];
int grid[1001][1001];

struct Crop
{
    int y, x;
    int sTime;
    int category;
    int water;
    int prevCrop;
    int nxtCrop;
} cropPool[100'001];
int cropCnt;

struct Block
{
    int crops;
    int activeCnt;
    int water;
} blocks[16][16];
int bShift, bSize;

inline bool isFullBlock(int by, int bx, int y1, int y2, int x1, int x2)
{
    return (y1 <= by * bSize) && (by * bSize + bSize - 1 <= y2) && (x1 <= bx * bSize) && (bx * bSize + bSize - 1 <= x2);
}

inline bool isVaildCrop(int cy, int cx, int y1, int y2, int x1, int x2)
{
    return y1 <= cy && cy <= y2 && x1 <= cx && cx <= x2;
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

    if (N <= 16)
        bShift = 0;
    else if (N <= 128)
        bShift = 3;
    else
        bShift = 6;
    bSize = 1 << bShift;

    int maxB = N >> bShift;
    for (int i = 0; i <= maxB; ++i)
    {
        for (int j = 0; j <= maxB; ++j)
        {
            Block &block = blocks[i][j];
            block.crops = 0;
            block.activeCnt = 0;
            block.water = 0;
        }
    }
}

int sow(int mTime, int mRow, int mCol, int mCategory)
{
    if (grid[mRow][mCol])
        return 0;
    int id = cropCnt++;
    Block &block = blocks[mRow >> bShift][mCol >> bShift];

    cropPool[id] = {mRow, mCol, mTime, mCategory, -block.water, 0, block.crops};
    if (block.crops)
        cropPool[block.crops].prevCrop = id;
    grid[mRow][mCol] = id;
    block.crops = id;
    block.activeCnt++;

    return 1;
}

int water(int mTime, int G, int mRow, int mCol, int mHeight, int mWidth)
{
    int y1 = mRow, y2 = mRow + mHeight - 1;
    int x1 = mCol, x2 = mCol + mWidth - 1;
    int by1 = y1 >> bShift, by2 = y2 >> bShift;
    int bx1 = x1 >> bShift, bx2 = x2 >> bShift;
    int ret = 0;
    for (int by = by1; by <= by2; ++by)
    {
        for (int bx = bx1; bx <= bx2; ++bx)
        {
            if (isFullBlock(by, bx, y1, y2, x1, x2))
            {
                blocks[by][bx].water += G;
                ret += blocks[by][bx].activeCnt;
            }
            else
            {
                int cur = blocks[by][bx].crops;
                while (cur)
                {
                    if (isVaildCrop(cropPool[cur].y, cropPool[cur].x, y1, y2, x1, x2))
                    {
                        cropPool[cur].water += G;
                        ret++;
                    }
                    cur = cropPool[cur].nxtCrop;
                }
            }
        }
    }
    return ret;
}

int harvest(int mTime, int L, int mRow, int mCol, int mHeight, int mWidth)
{
    int ret = 0;
    int y1 = mRow, y2 = mRow + mHeight - 1;
    int x1 = mCol, x2 = mCol + mWidth - 1;
    int by1 = y1 >> bShift, by2 = y2 >> bShift;
    int bx1 = x1 >> bShift, bx2 = x2 >> bShift;
    for (int by = by1; by <= by2; ++by)
    {
        for (int bx = bx1; bx <= bx2; ++bx)
        {
            if (blocks[by][bx].activeCnt == 0)
                continue;
            if (isFullBlock(by, bx, y1, y2, x1, x2))
            {
                int cur = blocks[by][bx].crops;
                while (cur)
                {
                    int g = growthTime[cropPool[cur].category];
                    if ((mTime - cropPool[cur].sTime) / g + cropPool[cur].water + blocks[by][bx].water < L)
                        return 0;
                    cur = cropPool[cur].nxtCrop;
                }
                ret += blocks[by][bx].activeCnt;
            }
            else
            {
                int cur = blocks[by][bx].crops;
                while (cur)
                {
                    if (isVaildCrop(cropPool[cur].y, cropPool[cur].x, y1, y2, x1, x2))
                    {
                        int g = growthTime[cropPool[cur].category];
                        if ((mTime - cropPool[cur].sTime) / g + cropPool[cur].water + blocks[by][bx].water < L)
                            return 0;
                        ret++;
                    }
                    cur = cropPool[cur].nxtCrop;
                }
            }
        }
    }
    if (ret == 0)
        return 0;

    for (int by = by1; by <= by2; ++by)
    {
        for (int bx = bx1; bx <= bx2; ++bx)
        {
            if (blocks[by][bx].activeCnt == 0)
                continue;
            if (isFullBlock(by, bx, y1, y2, x1, x2))
            {
                int cur = blocks[by][bx].crops;
                while (cur)
                {
                    grid[cropPool[cur].y][cropPool[cur].x] = 0;
                    cur = cropPool[cur].nxtCrop;
                }
                blocks[by][bx].activeCnt = 0;
                blocks[by][bx].crops = 0;
                blocks[by][bx].water = 0;
            }
            else
            {
                int cur = blocks[by][bx].crops;
                int prev = 0;
                while (cur)
                {
                    int cy = cropPool[cur].y, cx = cropPool[cur].x;
                    if (isVaildCrop(cy, cx, y1, y2, x1, x2))
                    {
                        grid[cy][cx] = 0;
                        blocks[by][bx].activeCnt--;
                        if (prev)
                            cropPool[prev].nxtCrop = cropPool[cur].nxtCrop;
                        else
                            blocks[by][bx].crops = cropPool[cur].nxtCrop;
                    }
                    else
                        prev = cur;
                    cur = cropPool[cur].nxtCrop;
                }
            }
        }
    }
    return ret;
}