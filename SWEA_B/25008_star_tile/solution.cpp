#include <unordered_map>
#include <algorithm>
#include <iostream>

#define MAX_SIZE 1000

#define uint unsigned int

struct StarTile
{
    int pos;
    int count;
};

int n;
int tileMap[MAX_SIZE][MAX_SIZE];
uint mask = 0x01FFFFFFU;
std::unordered_map<uint, StarTile> dict;

uint turnTile(uint tile)
{
    uint turned = 0;
    for (int i = 20; i <= 24; ++i)
    {
        for (int j = i; j >= 0; j -= 5)
        {
            turned <<= 1;
            turned |= (tile >> j) & 1;
        }
    }
    return turned;
}

uint addTile(uint tile, int y, int x)
{
    for (int i = 0; i < 4; ++i)
    {
        if (dict.find(tile) != dict.end())
        {
            dict[tile].count++;
            return tile;
        }
        tile = turnTile(tile);
    }
    dict[tile] = {y * 10000 + x, 1};
    return tile;
}

void init(int N, int mPlane[MAX_SIZE][MAX_SIZE])
{
    n = N;
    dict.clear();
    uint tile;
    int star;
    for (int i = 0; i <= n - 5; ++i)
    {
        star = 0;
        tile = 0;
        for (int x = 0; x < n; x++)
        {
            for (int y = i; y < i + 5; ++y)
            {
                star -= (tile >> 24) & 1;
                tile <<= 1;
                tile |= mPlane[y][x];
                star += mPlane[y][x];
            }
            tile &= mask;
            if (star == 7)
                tileMap[i][x - 4] = addTile(tile, i + 2, x - 2);
            else
                tileMap[i][x - 4] = 0;
        }
        for (int x = n - 4; x < n; ++x)
            tileMap[i][x] = 0;
    }
    for (int i = n - 4; i < n; ++i)
        for (int x = 0; x < n; ++x)
            tileMap[i][x] = 0;
}

int getCount(int mPiece[5][5])
{
    uint tile = 0;
    for (int x = 0; x < 5; ++x)
    {
        for (int y = 0; y < 5; ++y)
        {
            tile <<= 1;
            tile |= mPiece[y][x];
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        if (dict.find(tile) != dict.end())
            return dict[tile].count;
        tile = turnTile(tile);
    }
    return 0;
}

int getPosition(int mRow, int mCol)
{
    for (int y = std::max(0, mRow - 4); y <= mRow; ++y)
    {
        for (int x = std::max(0, mCol - 4); x <= mCol; ++x)
        {
            if (tileMap[y][x] != 0)
            {
                return dict[tileMap[y][x]].pos;
            }
        }
    }
    return 0;
}