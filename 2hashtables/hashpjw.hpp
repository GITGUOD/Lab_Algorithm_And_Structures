
#ifndef HASHPJW_H  
#define HASHPJW_H

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>


size_t fast_hash(const std::string& key) {
    size_t h = 0;
    size_t len = std::min(key.size(), size_t(8));
    for (size_t i = 0; i < len; i++) {
        h = (h << 4) + key[i];
    }
    return h;
}

// Base template declaration
template<typename K>
size_t hashpjw(const K& key);

// Specialization for std::string
template<>
size_t hashpjw<std::string>(const std::string& key) {
    uint32_t h = 0;
    uint32_t g;
    for (char c : key) {
        h = (h << 4) + static_cast<unsigned char>(c);
        if ((g = h & 0xf0000000)) {
            h ^= g >> 24;
            h ^= g;
        }
    }
    return h;
}

// Specialization for const char* (C-strings)
template<>
size_t hashpjw<const char*>(const char* const& key) {
    uint32_t h = 0;
    uint32_t g;
    for (const char* p = key; *p; ++p) {
        h = (h << 4) + static_cast<unsigned char>(*p);
        if ((g = h & 0xf0000000)) {
            h ^= g >> 24;
            h ^= g;
        }
    }
    return h;
}

// Specialization for int
template<>
size_t hashpjw<int>(const int& key) {
    // Convert int to bytes and hash
    uint32_t h = 0;
    uint32_t g;
    unsigned char* p = (unsigned char*)&key;
    for (size_t i = 0; i < sizeof(int); i++) {
        h = (h << 4) + p[i];
        if ((g = h & 0xf0000000)) {
            h ^= g >> 24;
            h ^= g;
        }
    }
    return h;
}

// Specialization for size_t
template<>
size_t hashpjw<size_t>(const size_t& key) {

    uint32_t h = 0;
    uint32_t g;
    unsigned char* p = (unsigned char*)&key;
    for (size_t i = 0; i < sizeof(size_t); i++) {
        h = (h << 4) + p[i];
        if ((g = h & 0xf0000000)) {
            h ^= g >> 24;
            h ^= g;
        }
    }
    return h;
}


#endif