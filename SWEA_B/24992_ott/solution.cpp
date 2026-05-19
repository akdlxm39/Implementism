#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#define USER_SIZE 1007
#define MOVIE_SIZE 10007

struct RESULT
{
    int cnt;
    int IDs[5];
};

struct movieCompare
{
    bool operator()(int a, int b);
};

struct watchCompare
{
    bool operator()(int a, int b);
};

struct Movie
{
    int id;
    int movieIndex;
    int score;
    int isValid;
    int genre;
    std::set<int, movieCompare>::iterator setIter;
    bool operator<(const Movie &other) const
    {
        if (score != other.score)
            return score > other.score;
        return movieIndex > other.movieIndex;
    }
} movies[MOVIE_SIZE];
int movieCnt;

std::unordered_map<int, int> movieMap;

bool movieCompare::operator()(int a, int b)
{
    if (movies[a].score != movies[b].score)
        return movies[a].score > movies[b].score;
    return movies[a].movieIndex > movies[b].movieIndex;
}
std::set<int, movieCompare> movieSet[6];

struct User
{
    int watchCnt;
    std::pair<int, int> watch[1001];
} users[USER_SIZE];
int userCnt;

void init(int N)
{
    userCnt = N;
    for (int i = 1; i <= userCnt; ++i)
        users[i].watchCnt = 0;
    movieCnt = 0;
    movieMap.clear();
    for (int i = 1; i <= 5; ++i)
        movieSet[i].clear();
    return;
}

// call:10,000
int add(int mID, int mGenre, int mTotal)
{
    if (movieMap.find(mID) != movieMap.end())
        return 0;
    Movie &newMovie = movies[movieCnt];
    newMovie.id = mID;
    newMovie.movieIndex = movieCnt;
    newMovie.score = mTotal;
    newMovie.isValid = true;
    newMovie.genre = mGenre;
    newMovie.setIter = movieSet[mGenre].insert(movieCnt).first;

    movieMap[mID] = movieCnt;
    ++movieCnt;
    return 1;
}

// call:1,000
int erase(int mID)
{
    auto it = movieMap.find(mID);
    if (it == movieMap.end())
        return 0;
    Movie &movie = movies[it->second];
    if (!movie.isValid)
        return 0;
    movie.isValid = false;
    movieSet[movie.genre].erase(movie.setIter);
    movieMap.erase(it);
    return 1;
}

// call: 30,000
int watch(int uID, int mID, int mRating)
{
    auto it = movieMap.find(mID);
    if (it == movieMap.end())
        return 0;
    int movieIndex = it->second;
    Movie &movie = movies[movieIndex];
    if (!movie.isValid)
        return 0;

    User &user = users[uID];
    for (int i = 0; i < user.watchCnt; ++i)
        if (user.watch[i].first == movieIndex)
            return 0;
    user.watch[user.watchCnt++] = {movieIndex, mRating};

    movieSet[movie.genre].erase(movie.setIter);
    movie.score += mRating;
    movie.setIter = movieSet[movie.genre].insert(movieIndex).first;

    return 1;
}

// call: 5,000
RESULT suggest(int uID)
{
    RESULT res;

    User &user = users[uID];
    int maxRating = 0, genre = 0, validCnt = 0;
    for (int i = user.watchCnt - 1; i >= 0 && validCnt < 5; --i)
    {
        if (!movies[user.watch[i].first].isValid)
            continue;
        if (maxRating < user.watch[i].second)
        {
            maxRating = user.watch[i].second;
            genre = movies[user.watch[i].first].genre;
        }
        validCnt++;
    }
    if (genre == 0)
    {
        std::priority_queue<std::pair<int, int>> pq;
        for (int g = 1; g <= 5; ++g)
        {
            int cnt = 0;
            for (int i : movieSet[g])
            {
                Movie &movie = movies[i];
                bool flag = movie.isValid;
                for (int j = 0; j < user.watchCnt && flag; ++j)
                    if (user.watch[j].first == i)
                        flag = false;
                if (flag)
                {
                    pq.push({-movie.score, -i});
                    if (pq.size() > 5)
                        pq.pop();
                    if (++cnt == 5)
                        break;
                }
            }
        }
        res.cnt = pq.size();
        for (int i = res.cnt - 1; i >= 0; --i)
        {
            res.IDs[i] = movies[-pq.top().second].id;
            pq.pop();
        }
    }
    else
    {
        res.cnt = 0;
        for (int i : movieSet[genre])
        {
            Movie &movie = movies[i];
            bool flag = movie.isValid;
            for (int j = 0; j < user.watchCnt && flag; ++j)
                if (user.watch[j].first == i)
                    flag = false;
            if (flag)
            {
                res.IDs[res.cnt++] = movie.id;
                if (res.cnt == 5)
                    break;
            }
        }
    }

    return res;
}