#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 4
#define CMD_INIT 100
#define CMD_CHANGE 200
#define CMD_CALCULATE 300

extern void init(int N, int M, char mGrade[][MAX_N][MAX_M]);
extern void change(int mRow, int mCol, int mDir, int mLength, char mChgGrade[MAX_M]);
extern char *calculate(int L, int sRow, int sCol, int eRow, int eCol);

static bool run()
{
    bool okay = false;
    int Q, N, M, L, mRow, mCol, mDir, mLength, sRow, sCol, eRow, eCol;
    char mGrade[MAX_N][MAX_N][MAX_M], mChgGrade[MAX_M], ans[MAX_M], *ret;

    bool debug = false;

    scanf("%d", &Q);

    for (int q = 0; q < Q; ++q)
    {
        int cmd;
        scanf("%d", &cmd);
        if (debug)
        {
            printf("%d : ", cmd);
        }
        switch (cmd)
        {
        case CMD_INIT:
            scanf("%d %d", &N, &M);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    scanf("%s", &mGrade[i][j]);
            init(N, M, mGrade);
            okay = true;
            break;
        case CMD_CHANGE:
            scanf("%d %d %d %d %s", &mRow, &mCol, &mDir, &mLength, &mChgGrade);
            change(mRow, mCol, mDir, mLength, mChgGrade);
            if (debug)
            {
                printf("%d %d %d %d %s :", mRow, mCol, mDir, mLength, mChgGrade);
            }
            break;
        case CMD_CALCULATE:
            scanf("%d %d %d %d %d %s", &L, &sRow, &sCol, &eRow, &eCol, &ans);
            if (debug)
            {
                printf("%d %d %d %d %d %s : ", L, sRow, sCol, eRow, eCol, ans);
            }
            ret = calculate(L, sRow, sCol, eRow, eCol);
            if (debug)
            {
                printf("%s : ", ret);
            }
            if (strcmp(ans, ret) != 0)
                okay = false;
            break;
        default:
            okay = false;
            break;
        }
        if (debug)
        {
            if (okay)
                printf("okay\n");
            else
                printf("fail\n");
        }
    }

    return okay;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("SWEA_B/26281_lockdown_city/sample_input.txt", "r", stdin);

    int TC, MARK;

    scanf("%d %d", &TC, &MARK);
    for (int tc = 1; tc <= TC; ++tc)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}