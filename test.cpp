#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int arr[10][10];

int main()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            arr[i][j] = 1;
    int cnt = 1;
    for (int i = 0; i < 3; ++i)
    {
        arr[2 + i][5 + i] = cnt++;
        arr[4 + i][1 + i] = cnt++;
        arr[1 + i][4 - i] = cnt++;
        arr[5 + i][6 - i] = cnt++;
    }
    // for (int i = 0; i < 3; ++i)
    // {
    //     arr[7 + i][10 - i] = cnt++;
    //     arr[10 - i][7 + i] = cnt++;
    // }
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (arr[i][j] >= 10)
                cout << char(arr[i][j] - 10 + 'A') << ' ';
            else
                cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}
