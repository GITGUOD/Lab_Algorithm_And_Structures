#ifndef HASH_H  
#define HASH_H

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>
#include "keyhash.hpp"
#include "hashpjw.hpp"
#include "Node.hpp"



// HashTable class
template <typename K, typename V>
class HashTable{

    private:

        size_t size;
        size_t count;

        Node<K, V>** table;

        
        size_t next_power_of_two(size_t n);
        
        public:
        std::vector<K> get_all_keys() const; // easy way for operations problem get all keys
        
        HashTable(size_t size=4);

        void insert(K key, V value);
        V* search(K key);
        bool remove(K key);

        void resize(size_t new_size);

        ~HashTable();

        float laod_factor() const { return (float)count/size;};
        size_t get_count() const{return count;}
        size_t get_size() const{return size;}
};


////////////////////////  hash.cpp here error with linking templates ///////

// alway power of two 
template<typename K, typename V>
size_t HashTable<K, V>::next_power_of_two(size_t n) {
    size_t power = 1;
    while (power < n) {
        power <<= 1;  // Multiply by 2
    }
    return power;
}

template<typename K, typename V>
std::vector<K> HashTable<K, V>::get_all_keys() const {
    std::vector<K> keys;
    for (size_t i = 0; i < size; i++) {
        Node<K, V>* current = table[i];
        while (current != nullptr) {
            keys.push_back(current->key);
            current = current->next;
        }
    }
    return keys;
}

// Constructor 
template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size):size(next_power_of_two(size)), count(0){    
    table = new Node<K, V>*[size];
    for(int i  = 0; i < size; i++){
        table[i] = nullptr;
    }
}

// Destructor
template<typename K, typename V>
HashTable<K, V>::~HashTable(){
    for(int i = 0; i <size; i++){
        Node<K, V>* current = table[i];
        while(current != nullptr){
            Node<K, V>* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}

// Resize function 
template<typename K, typename V>
void HashTable<K, V>::resize(size_t new_size) {
    // std::cout << "Resizing from " << size << " to " << new_size << std::endl; // For debugging
    
    new_size = next_power_of_two(new_size);

    // Save old table and size
    Node<K, V>** old_table = table;
    size_t old_size = size;
    
    // Create new table
    size = new_size;
    table = new Node<K, V>*[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = nullptr;
    }
    
    // Reset count
    count = 0;
    
    // Rehash all elements from old table
    for (size_t i = 0; i < old_size; i++) {
        Node<K, V>* current = old_table[i];
        while (current != nullptr) {
            Node<K, V>* next = current->next;
            
            // Insert into new table (simple rehash)
            // int new_index = keyhash(current->key) % size;
            // int new_index = hashpjw(current->key) % size;

            size_t hash = hashpjw(current->key);
            // size_t hash = fast_hash(current->key);
            int new_index = hash & (size-1);

            current->next = table[new_index];
            table[new_index] = current;
            count++;
            
            current = next;
        }
    }
    
    // Delete old table array, inte node vi anvander de
    delete[] old_table;
}

// Insert method with auto resizing
template<typename K, typename V>
void HashTable<K, V>::insert(K key, V value){

    // checking with load_factor is more or highter then 0.7
    if(laod_factor() > 0.75){
        resize(size *2); // by factor 2
    }

    // compute index by hash func
    // int index = keyhash(key) % size;
    // int index = hashpjw(key) % size;

    size_t hash = hashpjw(key);
    // size_t hash = fast_hash(key);
    int index = hash & (size -1);

    // chekc if already extis
    Node<K, V>* current = table[index];
    while (current != nullptr)
    {
        if(current->key == key){
            current->value = value;
            return; // key exists, just update the value
        }
        current = current->next;
    }

    // key doesnt exists in this step
    Node<K, V>* newNode = new Node<K, V>(key, value);
    newNode->next = table[index];
    table[index] = newNode;

    count++; // coutning for each time insert operation has been called
}

// serachin method
template<typename K, typename V>
V* HashTable<K, V>::search(K key){
    // Compute hash index
    // int index = keyhash(key) % size;
    // int index = hashpjw(key) % size;

    size_t hash = hashpjw(key);
    // size_t hash = fast_hash(key);
    int index = hash & (size-1);
    
    // Traverse the linked list at table[index]
    Node<K, V>* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return &(current->value);  
        }
        current = current->next;
    }
    
    return nullptr;  // no key
}


// removing method
template<typename K, typename V>
bool HashTable<K, V>::remove(K key){
    // compute hash index
    // int index = keyhash(key) % size;
    // int index = hashpjw(key) % size;

    size_t hash = hashpjw(key);
    // size_t hash = fast_hash(key);
    int index = hash &(size-1);

    Node<K, V>* current = table[index];
    Node<K, V>* prev = nullptr;
    
    // treverse the list
    while (current != nullptr)
    {
        if(current->key == key){
            if(prev == nullptr){
                //removing the first node
                table[index] = current->next;
            }else{
                //middle one
                prev->next = current->next;
            }
            delete current;

            count--; // counting down

            // adjusting our loadfactor
            if(laod_factor() < 0.25 && size > 4){
                resize( size / 2); // reducing by factor 2
            }
            return true;
        }
        prev = current;
        current = current->next;
    }
    

    return false;
    
}

#endif //HASH_H
