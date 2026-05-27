#include <iostream>

#define MAX_M 4
#define MAX_N 100

int gradeMap[MAX_N][MAX_N];
int mapSize, gradeSize, maxGrade;

inline int grade2int(const char grade[MAX_M])
{
    int res = 0;
    for (int i = 0; i < gradeSize; ++i)
    {
        res *= 27;
        if (*grade == '\0')
            continue;
        res += *(grade++) - 'A' + 1;
    }
    return res;
}

inline void int2grade(int grade, char ret[MAX_M])
{
    ret[3] = '\0';
    for (int i = gradeSize - 1; i >= 0; --i)
    {
        int cur = grade % 27;
        if (cur == 0)
            ret[i] = '\0';
        else
            ret[i] = 'A' + cur - 1;
        grade /= 27;
    }
}

void init(int N, int M, char mGrade[][MAX_N][MAX_M])
{
    mapSize = N;
    gradeSize = M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            gradeMap[i][j] = grade2int(mGrade[i][j]);
    maxGrade = 1;
    for (int i = 0; i < M; ++i)
        maxGrade *= 27;
    maxGrade -= 1;
}

void change(int mRow, int mCol, int mDir, int mLength, char mGrade[MAX_M])
{
    int grade = grade2int(mGrade);
    if (mDir == 0)
        for (int i = 0; i < mLength; ++i)
            gradeMap[mRow + i][mCol] = grade;
    else
        for (int i = 0; i < mLength; ++i)
            gradeMap[mRow][mCol + i] = grade;
}

struct Point
{
    int row, col;
};
const Point DIR[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct qNode
{
    int row, col;
    int count;
} queue[10011];
int head, rear;

int visited[MAX_N][MAX_N];
int visitCnt = 0;

bool bfs(int L, int sRow, int sCol, int eRow, int eCol, int curGrade)
{
    head = rear = 0;
    queue[rear++] = {sRow, sCol, L};
    visited[sRow][sCol] = ++visitCnt;
    while (head < rear)
    {
        qNode &cur = queue[head++];
        if (cur.row == eRow && cur.col == eCol)
            return true;
        if (cur.count == 0)
            continue;
        for (auto dir : DIR)
        {
            int nRow = cur.row + dir.row;
            int nCol = cur.col + dir.col;
            if (nRow < 0 || mapSize <= nRow || nCol < 0 || mapSize <= nCol ||
                visited[nRow][nCol] == visitCnt || gradeMap[nRow][nCol] < curGrade)
                continue;
            queue[rear++] = {nRow, nCol, cur.count - 1};
            visited[nRow][nCol] = visitCnt;
        }
    }
    return false;
}

char ret[MAX_M];
char *calculate(int L, int sRow, int sCol, int eRow, int eCol)
{
    int left = 1, right = maxGrade, ans = 0;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (bfs(L, sRow, sCol, eRow, eCol, mid))
        {
            ans = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    int2grade(ans, ret);
    return ret;
}