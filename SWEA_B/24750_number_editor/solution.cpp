#include <cstring>
using namespace std;

int cnt[1000];
int left1, right1, left2, right2;

void init(int mCnt1, int mDigitList1[30000], int mCnt2, int mDigitList2[30000])
{
    memset(cnt, 0, sizeof(cnt));
    int tmp = mDigitList1[0] * 10 + mDigitList1[1];
    for (int i = 2; i < mCnt1; ++i)
    {
        tmp %= 100;
        tmp *= 10;
        tmp += mDigitList1[i];
        cnt[tmp]++;
    }
    tmp = mDigitList2[0] * 10 + mDigitList2[1];
    for (int i = 2; i < mCnt2; ++i)
    {
        tmp %= 100;
        tmp *= 10;
        tmp += mDigitList2[i];
        cnt[tmp]++;
    }
    left1 = mDigitList1[0] * 10 + mDigitList1[1];
    right1 = mDigitList1[mCnt1 - 2] * 10 + mDigitList1[mCnt1 - 1];
    left2 = mDigitList2[0] * 10 + mDigitList2[1];
    right2 = mDigitList2[mCnt2 - 2] * 10 + mDigitList2[mCnt2 - 1];
}

void append(int mDir, int mNum1, int mNum2)
{
    if (mDir == 0)
    {
        for (int tmpNum1 = mNum1; tmpNum1 > 0; tmpNum1 /= 10)
        {
            left1 += tmpNum1 % 10 * 100;
            cnt[left1]++;
            left1 /= 10;
        }
        for (int tmpNum2 = mNum2; tmpNum2 > 0; tmpNum2 /= 10)
        {
            left2 += tmpNum2 % 10 * 100;
            cnt[left2]++;
            left2 /= 10;
        }
    }
    else if (mDir == 1)
    {
        for (int l = 1000; l > 0; l /= 10)
        {
            int tmpNum1 = mNum1 / l % 10;
            if (tmpNum1 == 0)
                continue;
            right1 *= 10;
            right1 += tmpNum1;
            cnt[right1]++;
            right1 %= 100;
        }
        for (int l = 1000; l > 0; l /= 10)
        {
            int tmpNum2 = mNum2 / l % 10;
            if (tmpNum2 == 0)
                continue;
            right2 *= 10;
            right2 += tmpNum2;
            cnt[right2]++;
            right2 %= 100;
        }
    }
}

int countNum(int mNum)
{
    int ret = cnt[mNum];
    if (right1 * 10 + left2 / 10 == mNum)
        ret++;
    if (right1 % 10 * 100 + left2 == mNum)
        ret++;
    return ret;
}