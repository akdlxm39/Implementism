#include <cstring>

#define HASH_SIZE 20011

struct RESULT
{
    int cnt;
    int IDs[5];
};

struct Movie
{
    int id;
    int genre;
    int total;
    int nxtHash;
    bool isDeleted;
} moviePool[10007];
int movieCnt;
int movieHash[HASH_SIZE];

struct User
{
    int id;
} users[1001];
int userCnt;

void init(int N)
{
    memset(movieHash, -1, sizeof(movieHash));
    movieCnt = 0;
    userCnt = N;
    for (int i = 1; i <= userCnt; ++i)
    {
        users[i].id = i;
    }
    return;
}

int add(int mID, int mGenre, int mTotal)
{
    int movieIdx = movieHash[mID % HASH_SIZE];
    while (movieIdx != -1)
    {
        if (moviePool[movieIdx].id == mID)
            return 0;
        movieIdx = moviePool[movieIdx].nxtHash;
    }
    moviePool[movieCnt].id = mID;
    moviePool[movieCnt].genre = mGenre;
    moviePool[movieCnt].total = mTotal;
    moviePool[movieCnt].isDeleted = false;
    moviePool[movieCnt].nxtHash = movieHash[mID % HASH_SIZE];
    movieHash[mID % HASH_SIZE] = movieCnt;
    movieCnt++;
    return 1;
}

int erase(int mID)
{
    int movieIdx = movieHash[mID % HASH_SIZE];
    while (movieIdx != -1)
    {
        if (moviePool[movieIdx].id == mID)
        {
            if (moviePool[movieIdx].isDeleted)
                return 0;
            moviePool[movieIdx].isDeleted = true;
            return 1;
        }
        movieIdx = moviePool[movieIdx].nxtHash;
    }
    return 0;
}

int watch(int uID, int mID, int mRating)
{
    return -1;
}

RESULT suggest(int uID)
{
    RESULT res;

    res.cnt = -1;

    return res;
}