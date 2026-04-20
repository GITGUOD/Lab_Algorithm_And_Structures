#include <iostream>
#include <string>
#include "Hash.hpp"



int main() {
    // Create hash table with size 5
    HashTable<std::string, int> ht(5);
    
    // Test insert and update
    std::cout << "=== Testing Insert ===" << std::endl;
    ht.insert("apple", 1);
    ht.insert("banana", 1);
    ht.insert("apple", 5);  
    
    // Test search
    std::cout << "\n=== Testing Search ===" << std::endl;
    int* val = ht.search("apple");
    if (val) std::cout << "apple: " << *val << std::endl;
    
    val = ht.search("banana");
    if (val) std::cout << "banana: " << *val << std::endl;
    
    val = ht.search("cherry");
    if (!val) std::cout << "cherry: not found" << std::endl;
    
    // Test remove
    std::cout << "\n=== Testing Remove ===" << std::endl;
    std::cout << "Remove banana: " << (ht.remove("banana") ? "success" : "fail") << std::endl;
    std::cout << "Remove banana again: " << (ht.remove("banana") ? "success" : "fail") << std::endl;
    
    val = ht.search("banana");
    if (!val) std::cout << "banana: gone" << std::endl;
    
    // Test multiple inserts (to check chaining)
    std::cout << "\n=== Testing Multiple Inserts ===" << std::endl;
    ht.insert("cat", 1);
    ht.insert("dog", 1);
    ht.insert("bird", 1);
    ht.insert("fish", 1);
    
    std::cout << "cat: " << *ht.search("cat") << std::endl;
    std::cout << "dog: " << *ht.search("dog") << std::endl;
    std::cout << "bird: " << *ht.search("bird") << std::endl;
    std::cout << "fish: " << *ht.search("fish") << std::endl;
    
    return 0;
}