#include <stdio.h>
#include <stdlib.h>

typedef struct client
{
    int num;
    int arrive_time;
    int delay_time;
    int c_num;
    int p_num;
    struct client *next;
} Client;

typedef struct staff
{
    int dispose_time;
    struct client *curr;
} Staff;

int n, m, k;
int a, b;
Staff re_c[9];
Staff re_p[9];

Client *start_queue = nullptr;
Client *end_queue = nullptr;

Client *c_queue = nullptr;
Client *c_end_queue = nullptr;

Client *p_queue = nullptr;
Client *p_end_queue = nullptr;

int t;
int sum;

int main()
{
    scanf("%d", &t);
    int st = t;
    for (t; t > 0; t--)
    {
        sum = 0;
        start_queue = nullptr;
        end_queue = nullptr;
        c_queue = nullptr;
        c_end_queue = nullptr;
        p_queue = nullptr;
        p_end_queue = nullptr;
        scanf("%d %d %d %d %d", &n, &m, &k, &a, &b);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &re_c[i].dispose_time);
            re_c[i].curr = nullptr;
        }
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &re_p[i].dispose_time);
            re_p[i].curr = nullptr;
        }
        for (int i = 0; i < k; i++)
        {
            Client *new_node = (Client *)malloc(sizeof(Client));
            scanf("%d", &new_node->arrive_time);
            new_node->num = i + 1;
            new_node->next = nullptr;
            if (start_queue == nullptr)
            {
                start_queue = new_node;
                end_queue = new_node;
            }
            else
            {
                end_queue->next = new_node;
                end_queue = new_node;
            }
        }
        int time = 0;
        while (1)
        {
            while (start_queue != nullptr)
            {
                if (start_queue->arrive_time == time)
                {
                    Client *temp = start_queue;
                    start_queue = start_queue->next;
                    temp->next = nullptr;
                    if (c_queue == nullptr)
                    {
                        c_queue = temp;
                        c_end_queue = temp;
                    }
                    else
                    {
                        c_end_queue->next = temp;
                        c_end_queue = temp;
                    }
                }
                else
                    break;
            }
            if (c_queue != nullptr)
            {
                for (int i = 0; i < n; i++)
                {
                    if (re_c[i].curr == nullptr)
                    {
                        Client *temp = c_queue;
                        c_queue = c_queue->next;
                        temp->next = nullptr;
                        re_c[i].curr = temp;
                        re_c[i].curr->delay_time = re_c[i].dispose_time;
                        re_c[i].curr->c_num = i + 1;
                    }
                    if (c_queue == nullptr)
                        break;
                }
            }
            if (p_queue != nullptr)
            {
                for (int i = 0; i < m; i++)
                {
                    if (re_p[i].curr == nullptr)
                    {
                        Client *temp = p_queue;
                        p_queue = p_queue->next;
                        temp->next = nullptr;
                        re_p[i].curr = temp;
                        re_p[i].curr->delay_time = re_p[i].dispose_time;
                        re_p[i].curr->p_num = i + 1;
                    }
                    if (p_queue == nullptrptr)
                        break;
                }
            }
            int p_check = 0;
            for (int i = 0; i < m; i++)
            {
                if (re_p[i].curr != nullptr)
                {
                    p_check = 1;
                    re_p[i].curr->delay_time--;
                    if (re_p[i].curr->delay_time <= 0)
                    {
                        if (re_p[i].curr->c_num == a && re_p[i].curr->p_num == b)
                        {
                            sum = sum + re_p[i].curr->num;
                        }
                        re_p[i].curr = nullptr;
                    }
                }
            }
            int c_check = 0;
            for (int i = 0; i < n; i++)
            {
                if (re_c[i].curr != nullptr)
                {
                    c_check = 1;
                    re_c[i].curr->delay_time--;
                    if (re_c[i].curr->delay_time == 0)
                    {
                        if (p_queue == nullptr)
                        {
                            p_queue = re_c[i].curr;
                            p_end_queue = re_c[i].curr;
                        }
                        else
                        {
                            p_end_queue->next = re_c[i].curr;
                            p_end_queue = re_c[i].curr;
                        }
                        re_c[i].curr = nullptr;
                    }
                }
            }
            if (start_queue == nullptr && c_queue == nullptr && p_queue == nullptr && c_check == 0 && p_check == 0)
                break;
            time++;
        }
        if (sum == 0)
            printf("#%d -1\n", st - (t - 1));
        else
            printf("#%d %d\n", st - (t - 1), sum);
    }
    return 0;
}