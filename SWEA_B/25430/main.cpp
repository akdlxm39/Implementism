#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int K, int sBuilding[], int eBuilding[], int mDistance[]);
extern void add(int sBuilding, int eBuilding, int mDistance);
extern int calculate(int M, int mCoffee[], int P, int mBakery[], int R);

/////////////////////////////////////////////////////////////////////////

#define MAX_E 30000
#define MAX_SHOP 1000
#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_CALC 300

static bool run()
{
    int q;
    scanf("%d", &q);

    int n, k, m, p, r;
    static int sBuildingArr[MAX_E], eBuildingArr[MAX_E], mDistArr[MAX_E], mCoffee[MAX_SHOP], mBakery[MAX_SHOP];
    int sBuilding, eBuilding, mDist;
    int cmd, ans, ret = 0;
    bool okay = false;

    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            okay = true;
            scanf("%d %d", &n, &k);
            for (int j = 0; j < k; ++j)
            {
                scanf("%d %d %d", &sBuildingArr[j], &eBuildingArr[j], &mDistArr[j]);
            }
            init(n, k, sBuildingArr, eBuildingArr, mDistArr);
            break;
        case CMD_ADD:
            scanf("%d %d %d", &sBuilding, &eBuilding, &mDist);
            add(sBuilding, eBuilding, mDist);
            break;
        case CMD_CALC:
            scanf("%d %d %d", &m, &p, &r);
            for (int j = 0; j < m; ++j)
            {
                scanf("%d", &mCoffee[j]);
            }
            for (int j = 0; j < p; ++j)
            {
                scanf("%d", &mBakery[j]);
            }
            ret = calculate(m, mCoffee, p, mBakery, r);
            scanf("%d", &ans);
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
    freopen("SWEA_B/25430/sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}