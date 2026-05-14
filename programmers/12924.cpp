#include <vector>
#include <iostream>

using namespace std;

int solution(int n)
{
    int answer = 0;
    int l = 0, r = 0;
    int num = 0;
    while (r < n)
    {
        num += ++r;
        while (num > n)
            num -= ++l;
        if (num == n)
            ++answer;
        cout << num << endl;
    }
    return answer;
}