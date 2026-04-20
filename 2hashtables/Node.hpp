#ifndef NODE_H
#define NODE_H

// Node class
template <typename K, typename V>
class Node{
    public:
        K key;
        V value;
        Node<K, V>* next;
        Node(K key, V value): key(key), value(value), next(nullptr){};
};
#endif