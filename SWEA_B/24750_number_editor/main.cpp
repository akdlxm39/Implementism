#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int mCnt1, int mDigitList1[30000], int mCnt2, int mDigitList2[30000]);
extern void append(int mDir, int mNum1, int mNum2);
extern int countNum(int mNum);

#define CMD_INIT 1
#define CMD_APPEND 2
#define CMD_COUNT 3

static int mDigitList1[30000];
static int mDigitList2[30000];
static char temp[30001];

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int mCnt1, mCnt2;
            scanf("%d", &mCnt1);
            scanf("%s", temp);
            for (int i = 0; i < mCnt1; i++)
            {
                mDigitList1[i] = temp[i] - '0';
            }
            for (int i = mCnt1; i < 30000; i++)
            {
                mDigitList1[i] = 0;
            }
            scanf("%d", &mCnt2);
            scanf("%s", temp);
            for (int i = 0; i < mCnt2; i++)
            {
                mDigitList2[i] = temp[i] - '0';
            }
            for (int i = mCnt2; i < 30000; i++)
            {
                mDigitList2[i] = 0;
            }
            init(mCnt1, mDigitList1, mCnt2, mDigitList2);
            ok = true;
        }
        else if (query == CMD_APPEND)
        {
            int mDir, mNum1, mNum2;
            scanf("%d %d %d", &mDir, &mNum1, &mNum2);
            append(mDir, mNum1, mNum2);
        }
        else if (query == CMD_COUNT)
        {
            int mNum;
            scanf("%d", &mNum);
            int ret = countNum(mNum);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("SWEA_B/24750/sample_input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}