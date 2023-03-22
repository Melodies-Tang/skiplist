#include <bits/stdc++.h>

template <typename T>
struct Less
{
    bool operator()(const T &a, const T &b) const
    {
        return a < b;
    }
};

template <typename T, typename Comp = Less<T>>
class skiplist
{
private:
    struct skiplist_node
    {
        int level;
        T value;
        skiplist_node **forward;
        skiplist_node() : value{0}, level{0}, forward{0} {}
        skiplist_node(const T& value, int level, skiplist_node *next = nullptr) : value(value), level(level)
        {
            forward = new skiplist_node *[level];
            for (int i = 0; i < level; ++i)
                forward[i] = next;
        }
        ~skiplist_node() { delete[] forward; }
    };

    static const int MAX_LEVEL = 32;
    int curr_level_cnt = 0;
    int curr_elem_cnt = 0;
    skiplist_node *head;
    skiplist_node *tail;

    Comp cmp;

    /*
     * Called when new skiplist_node is to be inserted. Return the count of levels this skiplist_node should be inserted into.
     */
    inline int random_level()
    {
        int level_cnt = 0;
        for (int i = 0; i < MAX_LEVEL; ++i)
            if (std::rand() % 2)
                ++level_cnt;
        return level_cnt;
    }

    inline skiplist_node *find_update(const T& value, skiplist_node *update[MAX_LEVEL])
    {
        skiplist_node *curr = head;
        for (int i = curr_level_cnt - 1; i >= 0; --i)
        {
            // In current level i, go forward until the next skiplist_node !<Comp> the target
            while (curr->forward[i] != tail && cmp(curr->forward[i]->value, value))
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
        skiplist_node *p;
        iterator() : p(nullptr){};
        iterator(skiplist_node *rhs) : p(rhs) {}
        skiplist_node *operator->() const { return (p); }
        skiplist_node &operator*() const { return *p; }
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

    skiplist() : head(new skiplist_node()), tail(new skiplist_node()), cmp()
    {
        srand((uint32_t)time(NULL));
        head->forward = new skiplist_node *[MAX_LEVEL];
        for (int i = 0; i < MAX_LEVEL; ++i)
            head->forward[i] = tail;
    }

    skiplist(const Comp& cmp) : head(new skiplist_node()), tail(new skiplist_node()), cmp(cmp)
    {
        srand((uint32_t)time(NULL));
        head->forward = new skiplist_node *[MAX_LEVEL];
        for (int i = 0; i < MAX_LEVEL; ++i)
            head->forward[i] = tail;
    }

    ~skiplist() = default;

    iterator insert(const T &value)
    {
        int insert_levels = random_level();
        if (insert_levels > curr_level_cnt)
        {
            curr_level_cnt = insert_levels;
        }
        skiplist_node *update[MAX_LEVEL]; // record the predecessor of inserted levels
        skiplist_node *found = find_update(value, update);

        skiplist_node *new_node = new skiplist_node(value, insert_levels);
        for (int i = insert_levels - 1; i >= 0; --i)
        {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
        ++curr_elem_cnt;
        return iterator(new_node);
    }

    bool erase(const T &value)
    {
        // Erase the first node with value {value}
        skiplist_node *update[MAX_LEVEL]; // record the predecessor of inserted levels
        skiplist_node *found = find_update(value, update);
        if (found->value != value)
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

    size_t size() const
    {
        return curr_elem_cnt;
    }

    int count(const T &value) const
    {
        auto it = find(value);
        int cnt = 0;
        while (it != tail) {
            ++cnt;
            ++it;
        }
        return cnt;
    }

    iterator end() const
    {
        return iterator(tail);
    }
    iterator begin() const
    {
        return iterator(head->forward[0]);
    }

    iterator find(const T &value)
    {
        skiplist_node *curr = head;
        for (int i = curr_level_cnt - 1; i >= 0; --i)
        {
            // In current level i, go forward until the next skiplist_node !<Comp> the target
            while (curr != tail && cmp(curr->forward[i]->value, value))
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
