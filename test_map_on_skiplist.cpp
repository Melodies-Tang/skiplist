#include "map_on_skiplist.hpp"

int main()
{
    std::unordered_map<>
    auto list = map_on_skiplist<int, int>();

    {
        auto list = map_on_skiplist<int, int>();
        list.insert(1, 1);
        list.insert(2, 1);
        list.insert(3, 1);
        list.insert(4, 1);
        std::cout << list.size() << std::endl;
        // map_on_skiplist<int, int>::iterator it = list.find(3);
        auto it = list.find(3);
        // it->key = 5;  // expression must be a modifiable lvalue
        it->value = 3;
        std::cout << list[3] << std::endl;
        list.erase(3);
        std::cout << list.size() << std::endl;
        std::cout << list[3] << std::endl;
        std::cout << list.size() << std::endl;
    }

    {
        // 使用lambda
        auto cmp = [](const std::string &a, const std::string &b) { return a.length() < b.length(); };
        map_on_skiplist<std::string, int, decltype(cmp)> list(cmp);
        // map_on_skiplist<std::string, int, decltype(cmp)> list_default;  // use of deleted function 'main()::<lambda(const string&, const string&)>::<lambda>()'
        list.insert("aab", 1321);
        list.insert("hello", 54342);
        list.insert("world", 544);
        for (auto it = list.begin(); it != list.end(); it++)
        {
            std::cout << it->key << " " << it->value << std::endl;
        }
    }

    std::cout << "==================================" << std::endl;

    {
        // 使用仿函数
        struct cmp
        {
            bool operator()(int a, int b)
            {
                return a > b;
            }
        };
        map_on_skiplist<int, int, cmp> list{};
        for (int i = 1; i <= 10; i++)
            list.insert(rand() % 20, rand());
        for (auto it = list.find(10); it != list.end(); it++)
        {
            std::cout << it->key << " " << it->value << std::endl;
        }
    }

    std::cout << "==================================" << std::endl;

    {
        // 默认小于号
        map_on_skiplist<int, int> list;
        list.insert(1, 3);
        list.insert(1, 3);
        list.insert(4, 3);
        list.insert(5, 3);
        list.insert(1, 3);
        list.insert(4, 3);
        for (auto it = list.begin(); it != list.end(); it++)
        {
            std::cout << it->key << " " << it->value << std::endl;
        }
    }

    {
        // 可以添加 T && 实现move语义
    }

    return 0;
}