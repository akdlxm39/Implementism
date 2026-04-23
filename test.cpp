#include <iostream>

using namespace std;

int solution(int n, int w, int num)
{
    if (n % w == 0)
        return (n / w) - ((num - 1) / w);

    int total_full_rows = n / w;
    int target_row = (num - 1) / w;
    int blocks_in_top_row = n % w;
    int target_col = (num - 1) % w + 1;

    bool is_top_row_reversed = (total_full_rows % 2 != 0);
    bool is_target_row_reversed = (target_row % 2 != 0);

    if (is_top_row_reversed != is_target_row_reversed)
        target_col = w - target_col + 1;

    int height_diff = total_full_rows - target_row;

    if (target_col <= blocks_in_top_row)
        height_diff += 1;

    return height_diff;
}