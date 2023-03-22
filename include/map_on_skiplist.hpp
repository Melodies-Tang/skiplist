#include <bits/stdc++.h>
#include "skiplist.hpp"

template <typename K, typename V, typename Comp = Less<K>>
class map_on_skiplist
{
private:
    struct kv_node {
        const K key;
        V value;

        kv_node(): key{0}, value{0} {}
        kv_node(K k, V v = V()): key(k), value(v) {}
    };

    struct Comp_key {
        bool operator()(const kv_node& a, const kv_node& b) {
            return Comp(a.key, b.key);
        }
    };

    skiplist<kv_node, Comp_key> container;

public:
    typedef typename skiplist<kv_node, Comp_key>::iterator iterator;
    // struct iterator {
    //     sl_iterator it;
    //     iterator() : it(nullptr){};
    //     iterator(kv_node *rhs) : it(rhs) {}
    //     kv_node *operator->() const { return (it); }
    //     kv_node &operator*() const { return *it; }
    //     bool operator==(const iterator &rhs) { return rhs.it == it; }
    //     bool operator!=(const iterator &rhs) { return !(rhs.it == it); }
    //     void operator++() { ++it; }
    //     iterator operator++(int)
    //     {
    //         iterator _init = it;
    //         ++it;
    //         return std::move(_init);
    //     }
    // };

    map_on_skiplist() : container() {}

    map_on_skiplist(const Comp& cmp) : container(cmp) {}

    ~map_on_skiplist() = default;

    iterator insert(const K &key, const V &value)
    {
        return container.insert(std::move(kv_node(key, value)));
    }

    bool erase(const K &key)
    {
        return container.erase(std::move(kv_node(key, V())));
    }

    V &operator[](const K &key)
    {
        iterator target = find(key);
        if (target != end())
        {
            return target->value;
        }
        else
        {
            return insert(key, V())->value;
        }
    }

    size_t size() const
    {
        return container.size();
    }

    int count(const K &key) const
    {
        return static_cast<int>(find(key)->key != end());
    }

    iterator end() const
    {
        return container.end();
    }
    iterator begin() const
    {
        return container.begin();
    }

    iterator find(const K &key)
    {
        return find(std::move(kv_node(key, 0)));
    }
};
