#include <iostream>
using namespace std;

struct Balloon
{
    int num;
    Balloon *left;
    Balloon *right;
    int pop()
    {
        int ret = 1;
        if (left != nullptr)
        {
            ret *= left->num;
            left->right = right;
        }
        if (right != nullptr)
        {
            ret *= right->num;
            right->left = left;
        }
        return ret;
    }
    void push(Balloon *b)
    {
        if (right != nullptr)
        {
            right->left = b;
        }
        b->right = right;
        b->left = this;
        this->right = b;
    }
};

int ret;
int n;
Balloon *head, *tail;

void init()
{
    ret = 0;
    for (Balloon *cur = head, *nxt; cur != nullptr; cur = nxt)
    {
        nxt = cur->right;
        delete cur;
    }
    head = nullptr;
    tail = nullptr;
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        Balloon *new_balloon = new Balloon{num, nullptr, nullptr};
        if (head == nullptr)
        {
            head = tail = new_balloon;
        }
        else
        {
            new_balloon->left = tail;
            tail->right = new_balloon;
            tail = new_balloon;
        }
    }
}

void dfs(int cnt, int total)
{
    if (cnt == n - 1)
    {
        if (ret < total + head->num)
            ret = total + head->num;
        return;
    }
    for (Balloon *cur = head->right; cur != nullptr; cur = cur->right)
    {
        Balloon *tmp = cur->left;
        dfs(cnt + 1, total + cur->pop());
        tmp->push(cur);
    }
    Balloon *tmp = head;
    head = head->right;
    dfs(cnt + 1, total + tmp->pop());
    head->left = tmp;
    tmp->right = head;
    head = tmp;
}

void solve()
{
    dfs(0, 0);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        init();
        input();
        solve();
        cout << "#" << tc << " " << ret << '\n';
    }

    return 0;
}