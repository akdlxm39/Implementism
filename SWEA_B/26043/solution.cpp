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

struct Word
{
    int no;
    int importance;
    char word[7];
    Word *left;
    Word *right;
} word_pool[MAX_WORD], *cur, *tmp;

struct Node
{
    int word_cnt;
    Node *children[26];
    Word *cur_word;
    Word *min_child_word;
    Word *max_child_word;

} trie[MAX_NODE], *root;

int word_cnt;
int node_cnt;

Word *get_new_word(const char mWord[7], int mImportance)
{
    Word *new_word = &word_pool[word_cnt++];
    new_word->no = word_cnt;
    new_word->importance = mImportance;
    memcpy(new_word->word, mWord, 7);
    new_word->left = new_word->right = nullptr;
    return new_word;
}

Node *get_new_node(Word *new_word = nullptr)
{
    Node *new_node = &trie[node_cnt++];
    memset(new_node, 0, sizeof(Node));
    new_node->min_child_word = new_node->max_child_word = new_word;
    return new_node;
}

void insert(Node *cur_node, Word *new_word, int depth = 0, Word *left = nullptr, Word *right = nullptr)
{
    if (new_word->word[depth] == '\0')
    {
        cur_node->cur_word = new_word;
        for (int i = 0; i < 26; ++i)
            if (cur_node->children[i] != nullptr)
            {
                left = cur_node->children[i]->min_child_word;
                break;
            }
        new_word->left = left;
        new_word->right = right;
        left->right = new_word;
        right->left = new_word;
        cur_node->min_child_word = new_word;
        return;
    }
    int i = ctoi(new_word->word[depth]);
    int l, r;
    for (l = i - 1; l >= 0; --l)
        if (cur_node->children[l] != nullptr)
        {
            left = cur_node->children[l]->max_child_word;
            break;
        }
    for (r = i + 1; r < 26; ++r)
        if (cur_node->children[r] != nullptr)
        {
            new_word->right = cur_node->children[r]->min_child_word;
            break;
        }
    if (cur_node->children[i] == nullptr)
    {
        cur_node->children[i] = get_new_node(new_word);
    }
    insert(cur_node->children[i], new_word, depth + 1);
    if (l == -1)
        cur_node->min_child_word = new_word;
    if (r == 26)
        cur_node->max_child_word = new_word;
}

void init()
{
    word_cnt = 0;
    node_cnt = 0;
    root = get_new_node();
    tmp = get_new_word("", 0);
    Word *new_word = get_new_word("a", 1);
    insert(root, new_word);
    cur = new_word;
    return;
}

PAGE add(char mWord[], int mImportance)
{
    Word *new_word = get_new_word(mWord, mImportance);
    insert(root, new_word);
    cur = new_word;
    PAGE res;
    res.no = cur->no;
    memcpy(res.word, new_word->word, 7);
    return res;
}

PAGE move(int mDir)
{
    if (mDir == -1)
        cur = cur->left;
    else
        cur = cur->right;
    PAGE res;
    res.no = cur->no;
    memcpy(res.word, cur->word, 7);
    return res;
}

Word *dfs(Node *cur_node, Word *max_word)
{
    if (cur_node->cur_word != nullptr)
        if (cur_node->cur_word->importance > max_word->importance)
            max_word = cur_node->cur_word;
    for (int i = 0; i < 26; ++i)
    {
        if (cur_node->children[i] != nullptr)
            max_word = dfs(cur_node->children[i], max_word);
    }
    return max_word;
}

PAGE search(char mStr[])
{
    Node *cur_node = root;
    for (int i = 0; mStr[i] != '\0'; ++i)
    {
        if (cur_node->children[ctoi(mStr[i])] == nullptr)
            return PAGE{-1, ""};
        cur_node = cur_node->children[ctoi(mStr[i])];
    }
    if (cur_node->cur_word == nullptr)
    {
        cur = dfs(cur_node, tmp);
    }
    else
        cur = cur_node->cur_word;
    PAGE res;
    res.no = cur->no;
    memcpy(res.word, cur->word, 7);
    return res;
}

PAGE go(int mNo)
{
    cur = &word_pool[mNo];
    PAGE res;
    res.no = cur->no;
    memcpy(res.word, cur->word, 7);
    return res;
}
