#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define MAXL (10)

const int CMD_INIT = 100;
const int CMD_ADD = 200;
const int CMD_TOP = 300;

extern void init(int N);
extern void addKeyword(char mKeyword[]);
extern int top5Keyword(char mRet[][MAXL + 1]);

static bool run()
{
    bool okay = false;
    int N, Q, user_ans, correct_ans;
    char mKeyword[MAXL + 1], mRet[5][MAXL + 1];
    scanf("%d", &Q);

    bool debug = false;

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
            scanf("%d", &N);
            init(N);
            okay = true;
            break;
        case CMD_ADD:
            scanf("%s", mKeyword);
            if (debug)
            {
                printf("%s : ", mKeyword);
            }
            addKeyword(mKeyword);
            break;
        case CMD_TOP:
            memset(mRet, 0, sizeof(mRet));
            scanf("%d", &correct_ans);
            if (debug)
            {
                printf("%d ", correct_ans);
            }
            user_ans = top5Keyword(mRet);

            if (correct_ans != user_ans)
                okay = false;

            for (int i = 0; i < correct_ans; i++)
            {
                char ans[MAXL + 1];
                scanf("%s", ans);
                if (debug)
                {
                    printf("%s ", ans);
                }
                if (strcmp(ans, mRet[i]) != 0)
                    okay = false;
            }
            if (debug)
            {
                printf(": %d ", user_ans);
                for (int i = 0; i < user_ans; i++)
                {
                    printf("%s ", mRet[i]);
                }
                printf(": ");
            }

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
    freopen("SWEA_B/25010/sample_input.txt", "r", stdin);

    int TC, MARK;

    scanf("%d %d", &TC, &MARK);
    for (int tc = 1; tc <= TC; ++tc)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}