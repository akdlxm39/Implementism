#include <iostream>
#include <unordered_map>

#define MAX_CITY 5'000
#define MAX_ROAD 25'000

struct Road
{
    int mId;
    int eCity, mDistance;
    int next;
} road_pool[MAX_ROAD];
int road_cnt;

int get_new_road(int mId, int eCity, int mDistance)
{
    road_pool[road_cnt].mId = mId;
    road_pool[road_cnt].eCity = eCity;
    road_pool[road_cnt].mDistance = mDistance;
    road_pool[road_cnt].next = -1;
    return road_cnt++;
}

struct City
{
    int roadList;
    int roadListEnd;
} cities[MAX_CITY];
int city_cnt;
int capital;

void init(int N, int mCapital, int K, int mId[], int sCity[], int eCity[], int mDistance[])
{
    road_cnt = 0;
    city_cnt = N;
    for (int i = 0; i < city_cnt; ++i)
        cities[i].roadList = -1;
    capital = mCapital;
    for (int i = 0; i < K; ++i)
        add(mId[i], sCity[i], eCity[i], mDistance[i]);
    return;
}

void add(int mId, int sCity, int eCity, int mDistance)
{
    City city = cities[sCity];
    if (city.roadList == -1)
    {
        int idx = get_new_road(mId, eCity, mDistance);
        city.roadList = idx;
        city.roadListEnd = idx;
    }
    else
    {
        int idx = get_new_road(mId, eCity, mDistance);
        road_pool[city.roadListEnd].next = idx;
        city.roadListEnd = idx;
    }
    return;
}

void remove(int mId)
{
    return;
}

int calculate(int mCity)
{
    return 0;
}