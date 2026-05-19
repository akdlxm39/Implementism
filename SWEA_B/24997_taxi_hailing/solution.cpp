#include <utility>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
#include <cmath>

// ----------------------------------------------------
// [상수 정의]
// 의미를 알기 어려운 하드코딩 숫자들을 상수로 명시
// ----------------------------------------------------
const int GRID_SIZE = 10;
const int INF = 987654321; // 초기 최소값 비교를 위한 무한대 값

// 문제에서 요구하는 반환 구조체
struct Result
{
    int mX, mY;
    int mMoveDistance;
    int mRideDistance;
};

// 전역 상태 변수 (가독성을 위해 변수명 구체화)
int city_N;  // 도시의 한 변 길이
int taxi_M;  // 전체 택시 개수
int limit_L; // 택시 호출이 가능한 최대 거리 (N / 10)

// 두 좌표 간의 맨해튼 거리를 반환하는 유틸리티 함수
inline int getDist(int y1, int x1, int y2, int x2)
{
    return std::abs(y1 - y2) + std::abs(x1 - x2);
}

// ----------------------------------------------------
// [택시 정보 구조체]
// ----------------------------------------------------
struct Taxi
{
    int y, x;         // 현재 택시의 좌표
    int moveDistance; // 총 운행 거리 (빈 차로 이동한 거리 + 손님 태운 거리)
    int rideDistance; // 손님을 태우고 이동한 거리
    int nxtTaxi;      // 동일한 격자(Block) 내에 있는 다음 택시를 가리키는 연결 리스트 포인터

    // 랭킹(best) set에서 현재 택시의 위치(iterator)를 저장. O(log N) 탐색/삭제를 위함
    std::set<std::pair<int, int>>::iterator setIter;
} taxi[2001];

// 상위 5대 랭킹을 실시간으로 유지하기 위한 이진 탐색 트리 구조
// { -rideDistance, taxi ID } 형태로 저장하여, 거리가 길고 ID가 작은 순으로 자동 정렬되게 함
std::set<std::pair<int, int>> best;

// ----------------------------------------------------
// [공간 분할(Spatial Hashing)을 위한 격자 구조체]
// 전체 맵을 최대 거리 L 단위의 10x10 격자로 나누어 탐색 공간을 최소화
// 각 격자는 내부에 있는 택시들을 연결 리스트(Linked List)로 관리함
// ----------------------------------------------------
struct Block
{
    int head;

    // 해당 격자에 택시(노드) 추가
    void push(int i)
    {
        taxi[i].nxtTaxi = head;
        head = i;
    }

    // 해당 격자 내에서 기준점(sy, sx)과 가장 가까운 택시 탐색
    std::pair<int, int> find(int sy, int sx)
    {
        std::pair<int, int> ret = {INF, -1}; // {거리, 택시 번호}

        // 연결 리스트를 순회하며 택시 검사
        for (int i = head; i != -1; i = taxi[i].nxtTaxi)
        {
            Taxi &cur = taxi[i];
            int curL = getDist(cur.y, cur.x, sy, sx);

            // 제한 거리(limit_L) 이하인 경우에만 갱신
            if (curL <= limit_L)
            {
                // 거리가 짧거나, 거리가 같을 경우 번호가 작은(min) 택시가 선택됨
                ret = std::min(ret, {curL, i});
            }
        }
        return ret;
    }

    // 해당 격자에서 특정 택시(노드) 제거
    void pop(int i)
    {
        if (head == i)
        {
            head = taxi[i].nxtTaxi;
            return;
        }
        int prev = -1;
        for (int cur = head; cur != -1; cur = taxi[cur].nxtTaxi)
        {
            if (cur == i)
            {
                taxi[prev].nxtTaxi = taxi[cur].nxtTaxi;
                return;
            }
            prev = cur;
        }
    }
} grid[GRID_SIZE][GRID_SIZE];

// ====================================================
// [API 함수 구현부]
// ====================================================

void init(int N, int M, int L, int mXs[], int mYs[])
{
    city_N = N;
    taxi_M = M;
    limit_L = L;

    // 격자 연결 리스트 초기화 (-1은 끝을 의미)
    std::memset(grid, -1, sizeof(grid));
    best.clear(); // 테스트 케이스 시작 시 랭킹 초기화 필수

    for (int i = 1; i <= M; ++i)
    {
        taxi[i].x = mXs[i - 1];
        taxi[i].y = mYs[i - 1];
        taxi[i].moveDistance = 0;
        taxi[i].rideDistance = 0;
        taxi[i].nxtTaxi = -1;

        // 초기 거리 0으로 세팅하여 랭킹 set에 삽입
        taxi[i].setIter = best.insert({0, i}).first;

        // 해당 택시가 위치한 물리적 격자에 편입 (좌표를 limit_L로 나누어 10x10 맵핑)
        grid[taxi[i].y / limit_L][taxi[i].x / limit_L].push(i);
    }
}

int pickup(int mSX, int mSY, int mEX, int mEY)
{
    // 출발지 좌표가 속한 기준 격자 계산
    int by = mSY / limit_L;
    int bx = mSX / limit_L;
    std::pair<int, int> choice = {INF, -1};

    // 주변 인접 격자(8방향 + 중앙)만 탐색하여 탐색 비용 최적화
    for (int y = by - 1; y <= by + 1; ++y)
    {
        if (y < 0 || GRID_SIZE <= y)
            continue; // 격자 범위를 벗어나면 패스

        for (int x = bx - 1; x <= bx + 1; ++x)
        {
            if (x < 0 || GRID_SIZE <= x)
                continue;

            // 인접 격자 내에 있는 가장 적합한 택시 후보를 갱신
            choice = std::min(choice, grid[y][x].find(mSY, mSX));
        }
    }

    int ret = choice.second; // 선택된 택시 번호 (실패 시 -1)

    if (ret != -1)
    {
        // 1. 기존에 택시가 속해있던 격자의 리스트에서 제거
        grid[taxi[ret].y / limit_L][taxi[ret].x / limit_L].pop(ret);

        // 2. 과거의 데이터를 랭킹 set에서 제거
        best.erase(taxi[ret].setIter);

        // 3. 누적 거리 계산 및 갱신
        int distToCustomer = getDist(taxi[ret].y, taxi[ret].x, mSY, mSX);
        int distToDestination = getDist(mSY, mSX, mEY, mEX);

        taxi[ret].moveDistance += (distToCustomer + distToDestination);
        taxi[ret].rideDistance += distToDestination;

        // 4. 새로운 데이터로 랭킹 set 갱신
        taxi[ret].setIter = best.insert({-taxi[ret].rideDistance, ret}).first;

        // 5. 택시의 위치를 최종 도착지로 갱신하고, 새로운 격자에 추가
        taxi[ret].y = mEY;
        taxi[ret].x = mEX;
        grid[mEY / limit_L][mEX / limit_L].push(ret);
    }

    return ret;
}

Result reset(int mNo)
{
    Result res;

    // 초기화 전 현재 상태를 백업
    res.mY = taxi[mNo].y;
    res.mX = taxi[mNo].x;
    res.mMoveDistance = taxi[mNo].moveDistance;
    res.mRideDistance = taxi[mNo].rideDistance;

    // 상태 초기화 로직 적용
    best.erase(taxi[mNo].setIter);
    taxi[mNo].moveDistance = 0;
    taxi[mNo].rideDistance = 0;

    // 초기화된 거리(0)로 랭킹 set 다시 삽입
    taxi[mNo].setIter = best.insert({-taxi[mNo].rideDistance, mNo}).first;

    return res;
}

void getBest(int mNos[])
{
    int i = 0;
    // best는 최상단부터 내림차순(음수 처리) 정렬되어 있으므로 순차적으로 가져오면 됨
    for (auto it : best)
    {
        mNos[i++] = it.second;
        if (i == 5)
            break; // 최대 5대까지만 추출
    }
}