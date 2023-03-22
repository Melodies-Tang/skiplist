#include <bits/stdc++.h>

template <typename T>
struct Less
{
    bool operator()(const T &a, const T &b) const
    {
        return a < b;
    }
};

template <typename K, typename V, typename Comp = Less<K>>
class skip_list
{
private:
    struct skip_list_node
    {
        int level;
        const K key;
        V value;
        skip_list_node **forward;
        skip_list_node() : key{0}, value{0}, level{0}, forward{0} {}
        skip_list_node(K k, V v, int level, skip_list_node *next = nullptr) : key(k), value(v), level(level)
        {
            forward = new skip_list_node *[level];
            for (int i = 0; i < level; ++i)
                forward[i] = next;
        }
        ~skip_list_node() { delete[] forward; }
    };

    static const int MAX_LEVEL = 32;
    int curr_level_cnt = 0;
    int curr_elem_cnt = 0;
    skip_list_node *head;
    skip_list_node *tail;

    Comp cmp;

    /*
     * Called when new skip_list_node is to be inserted. Return the count of levels this skip_list_node should be inserted into.
     */
    inline int random_level()
    {
        int level_cnt = 0;
        for (int i = 0; i < MAX_LEVEL; ++i)
            if (std::rand() % 2)
                ++level_cnt;
        return level_cnt;
    }

    inline skip_list_node *find_update(const K &key, skip_list_node *update[MAX_LEVEL])
    {
        skip_list_node *curr = head;
        for (int i = curr_level_cnt - 1; i >= 0; --i)
        {
            // In current level i, go forward until the next skip_list_node !<Comp> the target
            while (curr->forward[i] != tail && cmp(curr->forward[i]->key, key))
            {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        return curr = curr->forward[0];
    }

public:
    struct iterator
    {
        skip_list_node *p;
        iterator() : p(nullptr){};
        iterator(skip_list_node *rhs) : p(rhs) {}
        skip_list_node *operator->() const { return (p); }
        skip_list_node &operator*() const { return *p; }
        bool operator==(const iterator &rhs) { return rhs.p == p; }
        bool operator!=(const iterator &rhs) { return !(rhs.p == p); }
        void operator++() { p = p->forward[0]; }
        iterator operator++(int)
        {
            iterator _init = p;
            p = p->forward[0];
            return std::move(_init);
        }
    };

    template<typename _Requires = typename std::enable_if<std::is_default_constructible<Comp>::value>>
    skip_list() : head(new skip_list_node()), tail(new skip_list_node()), cmp()
    {
        srand((uint32_t)time(NULL));
        head->forward = new skip_list_node *[MAX_LEVEL];
        for (int i = 0; i < MAX_LEVEL; ++i)
            head->forward[i] = tail;
    }

    skip_list(const Comp& cmp) : head(new skip_list_node()), tail(new skip_list_node()), cmp(cmp)
    {
        srand((uint32_t)time(NULL));
        head->forward = new skip_list_node *[MAX_LEVEL];
        for (int i = 0; i < MAX_LEVEL; ++i)
            head->forward[i] = tail;
    }

    ~skip_list() = default;

    iterator insert(const K &key, const V &value)
    {
        int insert_levels = random_level();
        if (insert_levels > curr_level_cnt)
        {
            curr_level_cnt = insert_levels;
        }
        skip_list_node *update[MAX_LEVEL]; // record the predecessor of inserted levels
        skip_list_node *found = find_update(key, update);

        if (found->key == key)
        {
            // key already exists, modify and return iterator pointing to it
            found->value = value;
            return iterator(found);
        }

        skip_list_node *new_node = new skip_list_node(key, value, insert_levels);
        for (int i = insert_levels - 1; i >= 0; --i)
        {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
        ++curr_elem_cnt;
        return iterator(new_node);
    }

    bool erase(const K &key)
    {
        skip_list_node *update[MAX_LEVEL]; // record the predecessor of inserted levels
        skip_list_node *found = find_update(key, update);
        if (found->key != key)
            return false;
        for (int i = curr_level_cnt - 1; i >= 0; --i)
        {
            update[i]->forward[i] = found->forward[i];
        }
        delete found;
        while (curr_level_cnt > 0 && head->forward[curr_level_cnt - 1] != tail)
            --curr_level_cnt;
        --curr_elem_cnt;
    }

    V &operator[](const K &key)
    {
        iterator target = find(key);
        if (target != tail)
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
        return curr_elem_cnt;
    }

    int count(const K &key) const
    {
        auto it = find(key);
        if (it == tail())
            return 0;
        return static_cast<int>(key == it->key);
    }

    iterator end() const
    {
        return iterator(tail);
    }
    iterator begin() const
    {
        return iterator(head->forward[0]);
    }

    iterator find(const K &key)
    {
        skip_list_node *curr = head;
        for (int i = curr_level_cnt - 1; i >= 0; --i)
        {
            // In current level i, go forward until the next skip_list_node !<Comp> the target
            while (curr != tail && cmp(curr->forward[i]->key, key))
            {
                curr = curr->forward[i];
            }
        }
        if (curr == tail)
            return iterator(tail);
        else
        {
            return iterator(curr->forward[0]);
        }
    }
};
