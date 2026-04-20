#include "Hash.hpp"
#include <stddef.h>

// Base template - will give compile error if not specialized
template<typename K>
size_t keyhash(const K& key);

// Specialization for const char* (C-strings)
template<>
size_t keyhash<const char*>(const char* const& key) {
    size_t h = 0;
    const unsigned char* p = (const unsigned char*)key;
    while (*p) {
        h = 31 * h + *p++;
    }
    return h;
}

// Specialization for std::string
#include <string>
template<>
size_t keyhash<std::string>(const std::string& key) {
    size_t h = 0;
    for (char c : key) {
        h = 31 * h + c;
    }
    return h;
}

// Specialization for integers
template<>
size_t keyhash<int>(const int& key) {
    return key;  // Or a more complex hash if needed
}


// Constructor 
template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size):size(size), count(0){
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
            int new_index = keyhash(current->key) % size;
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
    int index = keyhash(key) % size;

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
    int index = keyhash(key) % size;
    
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
    int index = keyhash(key) % size;

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