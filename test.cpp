#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n = 1561881131;
    string s;
    while (n)
    {
        s += (n % 10 + '0');
        n /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << endl;
    return 0;
}