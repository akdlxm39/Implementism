#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define SHEEP 0
#define WOLF 1

struct Node
{
    int id;
    int childCnt;
    int children[2];
};
vector<Node> tree;

int dfs(int cur, int sheepCnt, int wolfCnt)
{
    pair<int, int> pii1, pii2;
}

int solution(vector<int> info, vector<vector<int>> edges)
{
    int answer = 0;
    tree.assign(info.size(), Node());
    for (int i = 0; i < info.size(); ++i)
        tree[i].id = info[i];
    for (int i = 0; i < edges.size(); ++i)
        tree[edges[i][0]].children[tree[edges[i][0]].childCnt++] = edges[i][1];
    for (Node node : tree)
    {
        cout << node.id << ' ' << node.childCnt << ' ' << node.children[0] << ' ' << node.children[1] << '\n';
    }
    answer = dfs(0, 0, 0);
    return answer;
}