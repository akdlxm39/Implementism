#include <cmath>
#include <iostream>

#define MAX_CITY 5'000
#define MAX_ROAD 25'000
#define MAX_DIST 500'007

struct Road
{
    int mId;
    int eCity, mDistance;
    Road *next;
} roadPool[MAX_ROAD];
int roadCnt;

Road *get_new_road(int mId, int eCity, int mDistance)
{
    Road *ret = &roadPool[roadCnt++];
    ret->mId = mId;
    ret->eCity = eCity;
    ret->mDistance = mDistance;
    ret->next = nullptr;
    return ret;
}

struct City
{
    int calcId;
    int totalDist;
    int maxDist;
    bool visited;
    Road *roadList;
    Road *roadListEnd;
} cities[MAX_CITY];
int cityCnt;
int capital;
int calcCnt;

void add(int mId, int sCity, int eCity, int mDistance);

void init(int N, int mCapital, int K, int mId[], int sCity[], int eCity[], int mDistance[])
{
    calcCnt = 0;
    roadCnt = 0;
    cityCnt = N;
    capital = mCapital;
    for (int i = 0; i < N; ++i)
    {
        cities[i].calcId = 0;
        cities[i].roadList = nullptr;
    }
    for (int i = 0; i < K; ++i)
        add(mId[i], sCity[i], eCity[i], mDistance[i]);
    return;
}

void add(int mId, int sCity, int eCity, int mDistance)
{
    Road *newRoad = get_new_road(mId, eCity, mDistance);
    if (cities[sCity].roadList == nullptr)
    {
        cities[sCity].roadList = newRoad;
        cities[sCity].roadListEnd = newRoad;
    }
    else
    {
        cities[sCity].roadListEnd->next = newRoad;
        cities[sCity].roadListEnd = newRoad;
    }
    return;
}

void remove(int mId)
{
    for (int i = 0; i < cityCnt; ++i)
    {
        if (cities[i].roadList != nullptr && cities[i].roadList->mId == mId)
        {
            cities[i].roadList = cities[i].roadList->next;
        }
        else
        {
            for (Road *cur = cities[i].roadList, *prev; cur != nullptr; prev = cur, cur = cur->next)
            {
                if (cur->mId == mId)
                {
                    prev->next = cur->next;
                    break;
                }
            }
        }
    }
    return;
}

void dfs(int curCity)
{
    int totalDist = MAX_DIST;
    int maxDist = 0;
    for (Road *curRoad = cities[curCity].roadList; curRoad != nullptr; curRoad = curRoad->next)
    {
        if (!cities[curRoad->eCity].visited && cities[curRoad->eCity].calcId != calcCnt)
        {
            cities[curRoad->eCity].visited = true;
            dfs(curRoad->eCity);
            cities[curRoad->eCity].visited = false;
        }
        if (cities[curRoad->eCity].calcId == calcCnt)
        {
            if (totalDist > cities[curRoad->eCity].totalDist + curRoad->mDistance)
            {
                totalDist = cities[curRoad->eCity].totalDist + curRoad->mDistance;
                maxDist = std::max(cities[curRoad->eCity].maxDist, curRoad->mDistance);
            }
            else if (totalDist == cities[curRoad->eCity].totalDist + curRoad->mDistance)
            {
                maxDist = std::min(maxDist, std::max(cities[curRoad->eCity].maxDist, curRoad->mDistance));
            }
        }
    }
    if (maxDist)
    {
        cities[curCity].totalDist = totalDist;
        cities[curCity].maxDist = maxDist;
    }
    cities[curCity].calcId = calcCnt;
}

int calculate(int mCity)
{
    if (mCity == 41)
    {
        int de = 1;
    }
    cities[mCity].calcId = ++calcCnt;
    cities[mCity].totalDist = 0;
    cities[mCity].maxDist = 0;
    cities[capital].maxDist = -1;
    dfs(capital);
    // std::cout << cities[capital].maxDist << '\n';
    return cities[capital].maxDist;
}