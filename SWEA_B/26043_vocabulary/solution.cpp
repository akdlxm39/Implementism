#include <algorithm>
#include <cstring>
using namespace std;

#define MAX_WORD 70'001
#define MAX_NODE 350'001
#define ctoi(c) int(c - 'a')

struct PAGE
{
    int no;
    char word[7];
};

struct Node
{
    int children[26];
    int child_word_cnt;
    int word_idx;
    int good_word_idx;
};

struct Word
{
    char word[7];
    int importance;
    int left;
    int right;
};

struct Result
{
    int no, idx;
};

Word word_pool[MAX_WORD];
Node trie[MAX_NODE];

int word_cnt;
int node_cnt;
int root;
Result cur;

int get_new_word(const char mWord[], int mImportance)
{
    int idx = word_cnt++;
    memcpy(word_pool[idx].word, mWord, 7);
    word_pool[idx].importance = mImportance;
    word_pool[idx].left = word_pool[idx].right = 0;
    return idx;
}

int get_new_node()
{
    int idx = node_cnt++;
    memset(&trie[idx], 0, sizeof(Node));
    return idx;
}

Result insert(const char mWord[], int mImportance)
{
    Result ret;
    ret.no = 1;
    ret.idx = get_new_word(mWord, mImportance);
    int ti = root;
    for (int wi = 0; mWord[wi] != '\0'; ++wi)
    {
        trie[ti].child_word_cnt++;
        if (word_pool[trie[ti].good_word_idx].importance < mImportance)
            trie[ti].good_word_idx = ret.idx;
        if (trie[ti].word_idx)
            ret.no++;
        int ci = ctoi(mWord[wi]);
        for (int li = ci - 1; li >= 0; --li)
            if (trie[ti].children[li])
                ret.no += trie[trie[ti].children[li]].child_word_cnt;
        if (trie[ti].children[ci] == 0)
            trie[ti].children[ci] = get_new_node();
        ti = trie[ti].children[ci];
    }
    trie[ti].child_word_cnt++;
    trie[ti].word_idx = ret.idx;
    trie[ti].good_word_idx = ret.idx;
    return ret;
}

void init()
{
    node_cnt = 0;
    word_cnt = 1;
    root = get_new_node();
    cur = insert("a", 1);
    return;
}

PAGE add(char mWord[], int mImportance)
{
    PAGE res;
    cur = insert(mWord, mImportance);
    res.no = cur.no;
    memcpy(res.word, word_pool[cur.idx].word, 7);
    return res;
}

Result find(char mStr[])
{
    Result ret;
    ret.no = 1;
    int ti = root;
    int si = 0;
    for (; mStr[si] != '\0'; ++si)
    {
        if (trie[ti].word_idx)
            ret.no++;
        int ci = ctoi(mStr[si]);
        if (trie[ti].children[ci] == 0)
        {
            ret.no = -1;
            return ret;
        }
        for (int li = 0; li < ci; ++li)
            if (trie[ti].children[li])
                ret.no += trie[trie[ti].children[li]].child_word_cnt;
        ti = trie[ti].children[ci];
    }
    if (trie[ti].word_idx == 0)
    {
        ret.idx = trie[ti].good_word_idx;
        for (; word_pool[ret.idx].word[si] != '\0'; ++si)
        {
            if (trie[ti].word_idx)
                ret.no++;
            int ci = ctoi(word_pool[ret.idx].word[si]);
            for (int li = 0; li < ci; ++li)
                if (trie[ti].children[li])
                    ret.no += trie[trie[ti].children[li]].child_word_cnt;
            ti = trie[ti].children[ci];
        }
    }
    else
        ret.idx = trie[ti].word_idx;
    return ret;
}

PAGE search(char mStr[])
{
    PAGE res;
    res.no = -1;
    Result ret = find(mStr);
    if (ret.no == -1)
        return res;
    cur = ret;
    res.no = cur.no;
    memcpy(res.word, word_pool[cur.idx].word, 7);
    return res;
}

PAGE go(int mNo)
{
    PAGE res;
    res.no = -1;
    cur.no = mNo;
    int last_no = cur.no;
    int ti = root;
    while (last_no)
    {
        if (trie[ti].word_idx)
            last_no--;
        if (last_no == 0)
            break;
        for (int ci : trie[ti].children)
        {
            if (ci == 0)
                continue;
            if (last_no - trie[ci].child_word_cnt <= 0)
            {
                ti = ci;
                break;
            }
            last_no -= trie[ci].child_word_cnt;
        }
    }
    cur.idx = trie[ti].word_idx;
    res.no = cur.no;
    memcpy(res.word, word_pool[cur.idx].word, 7);
    return res;
}

PAGE move(int mDir)
{
    return go(cur.no + mDir);
}