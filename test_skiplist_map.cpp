#include "include\skiplist_map.hpp"

int main()
{
    std::map<int, int> test_map;
    test_map.insert({1, 1});
    test_map.insert({1, 2});
    std::cout << "Test std::map " << test_map[1] << std::endl;

    {
        auto list = skip_list<int, int>();
        list.insert(1, 1);
        list.insert(2, 1);
        list.insert(3, 1);
        list.insert(5, 1);
        for (auto it = list.begin(); it != list.end(); it++)
        {
            std::cout << it->key << " " << it->value << std::endl;
        }
        // skip_list<int, int>::iterator it = list.find(3);
        auto f = list.find(3);
        // it->key = 5;  // expression must be a modifiable lvalue
        f->value = 3;
        std::cout << "Change value of 3 to 3" << std::endl;
        std::cout << list[3] << std::endl;
        list.erase(3);
        std::cout << "Erased 3" << std::endl;
        for (auto it = list.begin(); it != list.end(); it++)
        {
            std::cout << it->key << " " << it->value << std::endl;
        }
        f = list.find(4);
        if (f == list.end()) std::cout << "4 not found" << std::endl;
        else std::cout << "Need 4 but " << f->key << " found" << std::endl;
    }

    {
        // 使用lambda
        auto cmp = [](const std::string &a, const std::string &b) { return a.length() < b.length(); };
        skip_list<std::string, int, decltype(cmp)> list(cmp);
        // skip_list<std::string, int, decltype(cmp)> list_default;  // use of deleted function 'main()::<lambda(const string&, const string&)>::<lambda>()'
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
        skip_list<int, int, cmp> list{};
        for (int i = 1; i <= 10; i++)
            list.insert(rand() % 20, rand());
        for (auto it = list.find(10); it != list.end(); it++)
        {
            std::cout << it->key << " " << it->value << std::endl;
        }
    }

    std::cout << "==================================" << std::endl;

    {
        // 可以添加 T && 实现move语义
    }

    return 0;
}