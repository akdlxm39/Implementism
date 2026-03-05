#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define CMD_INIT (100)
#define CMD_ADD (200)
#define CMD_MOVE (300)
#define CMD_SEARCH (400)
#define CMD_GO (500)

struct PAGE
{
    int no;
    char word[7];
};

extern void init();
extern PAGE add(char mWord[], int mImportance);
extern PAGE move(int mDir);
extern PAGE search(char mStr[]);
extern PAGE go(int mNo);

static bool run()
{
    int Q;
    char mWord[7], mStr[7];
    int mImportance, mDir, mNo;

    PAGE res;

    int ret = -1, no;
    char ans[7];

    scanf("%d", &Q);

    bool okay = false;

    for (int q = 0; q < Q; ++q)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            init();
            okay = true;
            break;
        case CMD_ADD:
            scanf("%s %d", mWord, &mImportance);
            strcpy(ans, mWord);
            res = add(mWord, mImportance);
            scanf("%d", &no);
            if (res.no != no || strcmp(res.word, ans) != 0)
                okay = false;
            break;
        case CMD_MOVE:
            scanf("%d", &mDir);
            res = move(mDir);
            scanf("%d %s", &no, ans);
            if (res.no != no || strcmp(res.word, ans) != 0)
                okay = false;
            break;
        case CMD_SEARCH:
            scanf("%s", mStr);
            res = search(mStr);
            scanf("%d", &no);
            if (res.no != no)
                okay = false;
            if (no != -1)
            {
                scanf("%s", ans);
                if (strcmp(res.word, ans) != 0)
                    okay = false;
            }
            break;
        case CMD_GO:
            scanf("%d", &mNo);
            res = go(mNo);
            scanf("%s", ans);
            if (res.no != mNo || strcmp(res.word, ans) != 0)
                okay = false;
            break;
        default:
            okay = false;
            break;
        }
    }

    return okay;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("SWEA_B/26043/sample_input.txt", "r", stdin);

    int TC, MARK;

    scanf("%d %d", &TC, &MARK);
    for (int tc = 1; tc <= TC; ++tc)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}