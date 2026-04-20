# 7 Assignments if you selected separate chaining
1. Start with an array with one element and adjust its size as needed, i.e.
make the array bigger and smaller depending on the number of key-value
pairs in your hash table.
```main.cpp
int main() {
    HashTable<std::string, int> ht(1);  // size 1 
    std::string line;
    int i = 0;
    ...
}
```

2. What are suitable minimum and maximum numbers of key-value pairs (i.e.
list nodes) compared to the size of the array?
   * Maximum load factor (a_max) is typically 0.75 or 75% of array size.
     * When count / size > 0.75, reize by 2 factor size*2
     * This will keep the search and insert operations O(1) on average, worst case O(n)
   * Minium lead factor (a_min) is about 0.25 or 25% or array size 
     * When count / size < 0.25 and size > 1, shrink to halv size/2
     * this will preventing to wast memory when many items are deleted

3. If your implementation does not voluntarily reduce the size of the array,
force it to in order to test that it works!
```
// Insert method with auto resizing
template<typename K, typename V>
void HashTable<K, V>::insert(K key, V value){
    ...
    // checking with load_factor is more or highter then 0.7
    if(laod_factor() > 0.75){
        resize(size *2); // by factor 2
    }
    ...
    ...
}

// removing method
template<typename K, typename V>
bool HashTable<K, V>::remove(K key){
    ....
    // treverse the list
    while (current != nullptr)
    {
        if(current->key == key){
            if(prev == nullptr){
                ....
            }else{
                ...
            }
            ...

            count--; // counting down
            ...
            if(laod_factor() < 0.25 && size > 4){
                resize( size / 2); // reducing by factor 2
            }
            ...
        }
        ...
    }
    ...
}
```

# 10 More assignments for all hash tables
## 1. What do you think takes the most time in your implementations? (any answer is correct if you think that)
   * keyhash or compute the hash for long string
     * For example a char with 100 length will loop 100 times
     * 
``` Compute Hash
   size_t keyhash(const std::string& key) {
    size_t h = 0;
    for (char c : key) {  // O(length of key) - iterates every character
        h = 31 * h + c;
    }
    return h;
}
```
   * hashpjw also compute as time as keyhash
```
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
```
## 2 Two time consuming operations are division and remainder. In C/C++ integer remainder a % b is computed as

first test with  operation %, /
### result of %, /:
```
:~/Desktop/Algoritm_lab/2hashtables$ time ./main < data/secret/7huge.in
pg_ascii_tolower 308

real	0m5.693s
user	0m5.437s
sys	0m0.073s
:~/Desktop/Algoritm_lab/2hashtables$ time python3 reference.py < data/secret/7huge.in
pg_ascii_tolower 308

real	0m4.347s
user	0m3.975s
sys	0m0.132s
:~/Desktop/Algoritm_lab/2hashtables$ 

```
   * After changes:
     * resizing exponentionaly
     * change % mode with bitwise operator & and using shifting 
```
// alway power of two 
template<typename K, typename V>
size_t HashTable<K, V>::next_power_of_two(size_t n) {
    size_t power = 1;
    while (power < n) {
        power <<= 1;  // Multiply by 2
    }
    return power;
}
...
using power of two
// Resize function 
template<typename K, typename V>
void HashTable<K, V>::resize(size_t new_size) {
    ...
    new_size = next_power_of_two(new_size);
    ...
}
...
using & bitwise isntead of %
// compute index by hash func
// int index = keyhash(key) % size;
// int index = hashpjw(key) % size;
size_t hash = hashpjw(key);
int index = hash & (size -1);

```
### result
```
~/Desktop/Algoritm_lab/2hashtables$ time ./main < data/secret/7huge.in
pg_ascii_tolower 308

real	0m5.599s
user	0m5.374s
sys	0m0.062s
~/Desktop/Algoritm_lab/2hashtables$ time python3 reference.py < data/secret/7huge.in
pg_ascii_tolower 308

real	0m4.184s
user	0m3.979s
sys	0m0.080s
~/Desktop/Algoritm_lab/2hashtables$ 

```

### No Major differences att all.



## compareing hashpjw with fast_hash(just 8 first char)
### result
### testing with fast_hash
```
~/Desktop/Algoritm_lab/2hashtables$ g++ -std=c++11 -g -o main main.cpp
~/Desktop/Algoritm_lab/2hashtables$ time ./check_solution.sh ./main 
data/sample/1.in
Correct!
...
Correct!
data/secret/7huge.in
Correct!

real	0m15.702s
user	0m14.908s
sys	0m0.236s
~/Desktop/Algoritm_lab/2hashtables$ time ./check_solution.sh python3 reference.py 
data/sample/1.in
Correct!
...
Correct!
data/secret/7huge.in
Correct!

real	0m5.818s
user	0m5.283s
sys	0m0.267s
~/Desktop/Algoritm_lab/2hashtables$ time ./check_solution.sh ./main 
data/sample/1.in
Correct!
...
Correct!
data/secret/7huge.in
Correct!

real	0m16.422s
user	0m15.449s
sys	0m0.260s
~/Desktop/Algoritm_lab/2hashtables$ time python3 reference.py < data/secret/7huge.in
pg_ascii_tolower 308

real	0m4.020s
user	0m3.828s
sys	0m0.069s
~/Desktop/Algoritm_lab/2hashtables$ time ./main < data/secret/7huge.in
pg_ascii_tolower 308

real	0m13.320s
user	0m12.876s
sys	0m0.091s
```
### Testing with hashpjw
```
~/Desktop/Algoritm_lab/2hashtables$ g++ -std=c++11 -g -o main main.cpp
~/Desktop/Algoritm_lab/2hashtables$ time ./check_solution.sh ./main 
data/sample/1.in
Correct!
...
Correct!
data/secret/7huge.in
Correct!

real	0m7.520s
user	0m6.983s
sys	0m0.187s
~/Desktop/Algoritm_lab/2hashtables$ time ./main < data/secret/7huge.in
pg_ascii_tolower 308

real	0m5.700s
user	0m5.450s
sys	0m0.070s
```
