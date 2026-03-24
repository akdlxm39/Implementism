#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    unordered_map<int, pair<int, int>> map;
    map[1] = {4, 6};
    map[5] = {11, 11};

    // 얘는 같은 iterator 같지만, 실제로는 list<pair>의 iterator
    for (auto it : map)
    {
        cout << typeid(it).name() << '\n';

        cout << "key : " << it.first << '\n';
        cout << "pair.first : " << it.second.first << '\n';
        cout << "pair.second : " << it.second.second << '\n';
        cout << '\n';
    }

    // hashmap == iter를 pair로 관리해
    // 근데 아래는 iter가 그 페어의 주소를 가지고 있어
    // pair가 주르르르륵 있고, 그거를 "주소로" 순회하는 애;
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        cout << typeid(it).name() << '\n';
        cout << "key : " << it->first << '\n';
        cout << "pair.first : " << it->second.first << '\n';
        cout << "pair.second : " << it->second.second << '\n';
        cout << '\n';
    }

    return 0;
}