#include <string>

using namespace std;

bool solution(string s)
{
    bool answer = true;
    int x = 0;
    for (char c : s)
    {
        if (c == '(')
            x++;
        else if (c == ')')
        {
            if (x > 0)
                x--;
            else
            {
                answer = false;
                break;
            }
        }
    }
    if (x > 0)
        answer = false;
    return answer;
}