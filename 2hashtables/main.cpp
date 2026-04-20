#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Hash.hpp"

int main() {
    HashTable<std::string, int> ht(1);  // size 1 
    std::string line;
    int i = 0;
    
    // Read all lines from stdin
    while (std::getline(std::cin, line)) {
        // Remove carriage return if present 
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        // Skip empty lines as strip() removes whitespace
        if (line.empty()) {
            i++;
            continue;
        }
        
        bool is_present = (ht.search(line) != nullptr);
        bool remove_it = (i % 16 == 0);
        
        if (is_present) {
            if (remove_it) {
                ht.remove(line);
            } else {
                int* count = ht.search(line);
                if (count) {
                    ht.insert(line, (*count) + 1);
                }
            }
        } else if (!remove_it) {
            ht.insert(line, 1);
        }
        i++;
    }
    
    // Get all keys and find the one with max count (alphabetical first if tie)
    std::vector<std::string> keys = ht.get_all_keys();
    
    // Handle empty hash table case
    if (keys.empty()) {
        return 0;
    }
    
    // Find best word
    std::string best_word = keys[0];
    int best_count = *ht.search(best_word);
    
    for (const std::string& key : keys) {
        int count = *ht.search(key);
        if (count > best_count || (count == best_count && key < best_word)) {
            best_count = count;
            best_word = key;
        }
    }
    
    std::cout << best_word << " " << best_count << std::endl;
    
    return 0;
}