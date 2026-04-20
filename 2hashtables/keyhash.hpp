
#ifndef KEYHASH_H  
#define KEYHASH_H

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>


// Forward declaration - base template
template<typename K>
size_t keyhash(const K& key);

// Specializations
template<>
size_t keyhash<const char*>(const char* const& key);

template<>
size_t keyhash<std::string>(const std::string& key);

template<>
size_t keyhash<int>(const int& key);


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



#endif