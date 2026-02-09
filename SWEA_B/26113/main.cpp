#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int mCapital, int K, int mId[], int sCity[], int eCity[], int mDistance[]);
extern void add(int mId, int sCity, int eCity, int mDistance);
extern void remove(int mId);
extern int calculate(int mCity);

/////////////////////////////////////////////////////////////////////////

#define MAX_K 10000
#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_CALC 400

static bool run()
{
    int q;
    scanf("%d", &q);

    int n, m, k;
    int mIdArr[MAX_K], sCityArr[MAX_K], eCityArr[MAX_K], mDistArr[MAX_K];
    int mId, mCity, sCity, eCity, mDist;
    int cmd, ans, ret = 0;
    bool okay = false;

    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            okay = true;
            scanf("%d %d %d", &n, &m, &k);
            for (int j = 0; j < k; ++j)
            {
                scanf("%d %d %d %d", &mIdArr[j], &sCityArr[j], &eCityArr[j], &mDistArr[j]);
            }
            init(n, m, k, mIdArr, sCityArr, eCityArr, mDistArr);
            break;
        case CMD_ADD:
            scanf("%d %d %d %d", &mId, &sCity, &eCity, &mDist);
            add(mId, sCity, eCity, mDist);
            break;
        case CMD_REMOVE:
            scanf("%d", &mId);
            remove(mId);
            break;
        case CMD_CALC:
            scanf("%d %d", &mCity, &ans);
            ret = calculate(mCity);
            if (ans != ret)
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
    freopen("SWEA_B/26113/sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}