#include <iostream>
#include <vector>
#include <algorithm> // sort함수

using namespace std;

int N, M;
int board[51][51]; // 격자판 (0은 빈칸, 숫자는 상자 번호)

// 좌표를 담는 전용 구조체
struct Point {
    int y, x; // 행(row), 열(col)
};

// 상자의 정보를 담는 구조체 
struct Box {
    int k, h, w, y, x; // 택배번호, 세로 크기, 가로 크기, y좌표 ,x좌표
    bool removed; // 삭제된 것인가
};

// 상자 정보 저장 벡터
vector<Box> boxes;

// 이동 방향: 아래(0), 왼쪽(1), 오른쪽(2)
int dy[3] = {1,0,0};
int dx[3] = {0,-1,1};

// [정렬 함수] 
// ID가 작은 박스 우선
bool compareID(Box a, Box b) {return a.k < b.k;}
// 바닥에 가까운 박스 우선
bool compareBottom(Box a, Box b) {return (a.y + a.h) > (b.y+b.h);}

// 해당 위치에 상자를 놓을 수 있는지 체크
bool canPut(int h, int w, int y, int x, int d){
    // 상자 테두리 설정
    int y1 = y, y2 = y+h-1;     // 시작행, 바닥행
    int x1 = x, x2 = x+w-1;     // 시작열, 오른쪽 끝 열

    if(d==0) y1 = y+h-1;  // 아래: '바닥 면'만 검사! (시작행 y1을 바닥행 y2와 같게 만듦)
    else if (d==1) x2 = x; // 왼쪽: '왼쪽 면'만 검사! (끝열 x2를 시작열 x1과 같게 만듦)
    else x1 = x + w -1;  // 오른쪽: '오른쪽 면'만 검사! (시작열 x1을 끝열 x2와 같게 만듦)

    for(int ny = y1; ny <= y2; ny++){
        for(int nx = x1; nx <= x2; nx++){
            // 격자 밖으로 나갔는지 확인
            if(ny < 0 || ny >= N || nx < 0 || nx >= N)
                return false;
            // 이미 다른상자있으면
            if(board[ny][nx] != 0)
                return false; // 못 들어감
        }
    }
    return true; // 비어있어서 가도됌
}

// 상자를 특정 방향(d)으로 끝까지 밀기
Point moveBox(int h, int w, int y, int x, int d){
    int cy = y, cx = x;

    while (true){
        int ny = cy + dy[d];
        int nx = cx + dx[d];

        if(canPut(h, w, ny, nx, d)){
            cy = ny;
            cx = nx;
        } else {
            break;
        }
    }
    // 최종 위치를 구조체로 반환
    return {cy,cx};
}

// 상자 지우기
void removeBox(int idx){
    for(int i= boxes[idx].y; i<boxes[idx].y + boxes[idx].h; i++)
        for(int j = boxes[idx].x; j<boxes[idx].x + boxes[idx].w; j++)
            board[i][j] = 0;
}

// 상자 다시 그리기
void putBox(int idx){
    for(int i= boxes[idx].y; i<boxes[idx].y + boxes[idx].h; i++)
        for(int j = boxes[idx].x; j<boxes[idx].x + boxes[idx].w; j++)
            board[i][j] = boxes[idx].k;
}

int main(){
    // 빠른 입출력
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    // 이중 배열은 이미 0으로 초기화되어 있거나, 아래처럼 초기화 가능
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) board[i][j] = 0;

    // 1. 처음 상자들 떨어뜨리기
    for(int i=0; i<M; i++){
        int k, h, w, c1;
        cin >> k >> h >> w >> c1;
        
        //  moveBox(h,w,y(0),x,d)
        Point p = moveBox(h,w,0,c1-1,0);
        boxes.push_back({k, h, w, p.y, p.x, false});
        putBox(i);
    }

    // 2. M번의 탈출 턴 진행
    for(int turn =0; turn <M; turn++){
        // 1) 탈출 방향 결정 (0,2,4.. 는 왼쪽 턴)
        int dir;
        if(turn%2==0) dir =1;    // 왼쪽
        else dir =2;     // 오른쪽

        // 먼저 탈출할 상자를 찾는다
        // 2) 번호가 작은 상자부터 하기 위해 ID 순서대로 정렬
        sort(boxes.begin(), boxes.end(), compareID);
        
        // 3) 상자 한나씩 꺼내서
        for(int i=0; i<boxes.size(); i++){
            if(boxes[i].removed) continue;

            // i번째 상자 지우기
            removeBox(i);

            // 끝까지 밀어보기
            Point p = moveBox(boxes[i].h, boxes[i].w, boxes[i].y, boxes[i].x, dir);

            // 벽끝이니?
            bool success = false;
            if(dir == 1 && p.x == 0) success = true;
            if(dir == 2 && p.x + boxes[i].w == N) success = true;

            if (success){
                cout << boxes[i].k << "\n";
                boxes[i].removed = true;
                break;    // 한 명 나갔으니 이번 턴 종료
            } else{
                putBox(i);     // 못 나갔으면 다시 그리기
            }
        }

        // 3. 중력적용
        sort(boxes.begin(), boxes.end(), compareBottom);
        for(int i=0; i<boxes.size(); i++){
            if(boxes[i].removed) continue;

            removeBox(i);

            // 아래(방향 0)로 끝까지 밀어봄
            Point p = moveBox(boxes[i].h, boxes[i].w, boxes[i].y, boxes[i].x, 0);

            // boxes 새로 도착한 곳으로 업데이트
            boxes[i].y = p.y , boxes[i].x = p.x;

            putBox(i);
         }
    }
    return 0;
}