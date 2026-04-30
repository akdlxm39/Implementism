#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

int solution(string message, vector<vector<int>> spoiler_ranges)
{
    int answer = 0;
    int sp_idx = 0;
    int sp_start = spoiler_ranges[sp_idx][0], sp_end = spoiler_ranges[sp_idx][1];
    string word;
    bool is_reveal = true;
    set<string> spoil_words;
    set<string> secret_words;
    for (int i = 0; i < message.length(); ++i)
    {
        spoiler_ranges[sp_idx][0];
        if (message[i] == ' ')
        {
            if (is_reveal)
                spoil_words.insert(word);
            else
                secret_words.insert(word);
            is_reveal = true;
            word = "";
        }
        else
        {
            word += message[i];
            if (sp_end < i)
            {
                if (++sp_idx >= spoiler_ranges.size())
                    sp_start = sp_end = 20001;
                else
                {
                    sp_start = spoiler_ranges[sp_idx][0];
                    sp_end = spoiler_ranges[sp_idx][1];
                }
            }
            if (sp_start <= i && i <= sp_end)
            {
                is_reveal = false;
            }
        }
    }
    if (is_reveal)
        spoil_words.insert(word);
    else
        secret_words.insert(word);
    for (auto word : spoil_words)
        secret_words.erase(word);
    answer = secret_words.size();
    return answer;
}