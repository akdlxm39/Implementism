#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> class Heap
{
    vector<T> heap;
    static constexpr size_t MAX_SIZE = 131'072;
    void heapify_up();
    void heapify_down();

  public:
    Heap();
    void push(T val);
    void pop();
    bool empty() const
    {
        return heap.empty();
    }
    size_t size() const
    {
        return heap.size();
    }
    T top() const
    {
        return heap.empty() ? T() : heap.front();
    }
};

template <typename T> Heap<T>::Heap()
{
    heap.reserve(MAX_SIZE);
}

template <typename T> void Heap<T>::push(T val)
{
    if (heap.size() == MAX_SIZE)
        return;
    heap.push_back(val);
    heapify_up();
}

template <typename T> void Heap<T>::pop()
{
    if (heap.size() == 0)
        return;
    if (heap.size() == 1)
    {
        heap.pop_back();
        return;
    }
    heap[0] = heap.back();
    heap.pop_back();
    heapify_down();
}

template <typename T> void Heap<T>::heapify_up()
{
    size_t idx = heap.size() - 1;
    while (idx > 0 && heap[idx] > heap[(idx - 1) / 2])
    {
        swap(heap[idx], heap[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

template <typename T> void Heap<T>::heapify_down()
{
    size_t idx = 0;
    while (idx * 2 + 1 < heap.size())
    {
        size_t biggest = idx * 2 + 1;
        if (idx * 2 + 2 < heap.size() && heap[idx * 2 + 2] > heap[biggest])
            biggest = idx * 2 + 2;
        if (heap[idx] >= heap[biggest])
            break;
        swap(heap[idx], heap[biggest]);
        idx = biggest;
    }
}

void solve()
{
    int n, x;
    Heap<int> heap;
    cin >> n;
    while (n--)
    {
        cin >> x;
        if (x > 0)
        {
            heap.push(x);
        }
        else
        {
            cout << heap.top() << '\n';
            heap.pop();
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--)
        solve();

    return 0;
}