# KV storage on two lines

## skiplist_map.hpp
Provide 
```cpp
template <typename K, typename V, typename Comp = Less<K>> 
class skip_list;
```

 which is a template class provide basic CRUD interface as a KV storage. The template parametre ```K, V, Comp``` gives potential key and value types, along with a Compare function provided by user by a functor or wrapped lambda. _When transfer_ `decltype(lambda)` _as the parametre_ `Comp`_, you should also pass the lambda itself to it's constructor_

```cpp
iterator insert(const K &key, const V &value);
bool erase(const K &key);
V &operator[](const K &key);
iterator find(const K &key);
int count(const K &key) const;
iterator end() const;
iterator begin() const;
size_t size() const;
```

## skiplist.hpp
A more basic implementation of skiplist, gives
```cpp
template <typename T, typename Comp = Less<T>>
class skiplist;
```
which can take single value type `T` as the type of a single node value. Provide interfaces as:
```cpp
iterator insert(const T &value);
bool erase(const T &value);
iterator find(const T &value);
int count(const T &value) const;
iterator end() const;
iterator begin() const;
size_t size() const;
```

## map_on_skiplist.hpp
Based on the basic skiplist, construct a map-like container
```cpp
template <typename K, typename V, typename Comp = Less<K>>
class map_on_skiplist;
```
The basic idea is to wrap the `class skiplist` into this container by the way of combination, still some debugging required. (Different from the method `std::map` uses, where the base container```
_Rb_tree<key_type, value_type, _Select1st<value_type>, key_compare, _Pair_alloc_type>``` is already using `K-V` structure, I want to struggle with template to get a different design, where the underlying `skiplist` takes `kv_node` as it's basic `typename T`, and de-pair work done in the upper level, i.e. in the `map_on_skiplist`