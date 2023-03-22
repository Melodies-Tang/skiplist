#include "skiplist.hpp"

int main()
{
    {
        auto list = skiplist<int>();
        list.insert(1);
        list.insert(2);
        list.insert(3);
        list.insert(3);
        list.insert(3);
        list.insert(4);
        std::cout << "Inserted 1 2 3 3 3 4" << std::endl;
        for (auto it = list.begin(); it != list.end(); it++)
        {
            std::cout << it->value << std::endl;
        }
        std::cout << std::endl
                  << "Find and output the first node 3" << std::endl;
        // skiplist<int>::iterator it = list.find(3);
        auto f = list.find(3);
        std::cout << f->value << std::endl;
        // it->key = 5;  // expression must be a modifiable lvalue
        list.erase(3);
        std::cout << std::endl
                  << "After erasing the first node 3" << std::endl;
        for (auto it = list.begin(); it != list.end(); it++)
        {
            std::cout << it->value << std::endl;
        }
    }

    std::cout << "==================================" << std::endl;

    {
        // 使用lambda
        auto cmp = [](const std::string &a, const std::string &b) { return a.length() < b.length(); };
        skiplist<std::string, decltype(cmp)> list(cmp);
        // skiplist<std::string, int, decltype(cmp)> list_default;  // use of deleted function 'main()::<lambda(const string&, const string&)>::<lambda>()'
        list.insert("aab");
        list.insert("hello");
        list.insert("world");
        for (auto it = list.begin(); it != list.end(); it++)
        {
            std::cout << it->value << std::endl;
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
        skiplist<int, cmp> list{};
        for (int i = 1; i <= 10; i++)
            list.insert(rand() % 20);
        for (auto it = list.find(10); it != list.end(); it++)
        {
            std::cout << it->value << std::endl;
        }
    }

    std::cout << "==================================" << std::endl;

    {
        // 可以添加 T && 实现move语义
    }

    return 0;
}