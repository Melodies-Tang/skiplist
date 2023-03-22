# KV storage on two lines

## skiplist_map.hpp
Provide `template <typename K, typename V, typename Comp = Less<K>> class skip_list`, which is a template class provide basic CRUD interface as a KV storage. The template parametre `K, V, Comp` gives potential key and value types, along with a Compare function provided by user by a functor or wrapped lambda.


