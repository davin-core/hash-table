#include<string>
#include<memory>
#include<string>
#include<iostream>
#include "hash_table.h"
#include "prime.h"


// this function allocate memory for the size of an ht_item 
// and initialize the key and value of the ht_item with the provided parameters
// we don't use static because it has to be called from other files
std::unique_ptr<ht_item> ht_new_item(const std::string&key, const std::string& value){
    return std::make_unique<ht_item>(ht_item{key, value});
}
// this function allocate memory for the size of a hash_table 
// initialize the size and items of the hash_table with the provided parameters
std::unique_ptr<hash_table> ht_new(int size){
    auto table = std::make_unique<hash_table>();
    table->size = size;
    table->items.resize(size); // vector of unique_ptr<ht_item> with size 'size'
    return table;
}


// we use unique points to manage memory, so we don't need to manually delete the hash_table or its items.


// here we can use static because this function is only used within this file to delete an ht_item
//static void ht_del_item(std::unique_ptr<ht_item>& item){
//    item.reset(); // reset the unique_ptr to delete the ht_item
//}

// this is the function to delete the hash_table, it iterates 
// through each item in the hash_table and deletes it using ht_del_item, then resets the unique_ptr to delete the hash_table itself.
//void ht_del_hash_table(std::unique_ptr<hash_table>& table){
//    for (auto& item : table->items) {
//        ht_del_item(item); // delete each item in the hash table
//    }
//    table.reset(); // reset the unique_ptr to delete the hash_table
//}

// hashing function to calculate the index for a given key
// algoirthm: 
// take string, a number between 0 and m. Our desired bucket array length
// return an even distribution of the hash values for the keys. 
// If not evenly distributed, we will have more collisions and the performance of the hash table will degrade. 
static int ht_hash(const std::string &key, int a, int m) {
    long hash = 0;
    for(char c : key) {
        hash = (hash * a + c) % m;
    }
    return static_cast<int>(hash);
}

// this function is used to insert a key-value pair into the hash table
void _ht_insert(std::unique_ptr<hash_table>& table, const std::string& key, const std::string& value) {
    if(table->count >= table->size /0.7) { 
        _ht_resize_up(table);
    }
    int index = ht_hash(key, 31, table->size); // calculate the index for the given key using the hash function
    int start = index; // to keep track of the starting index for linear probing
    while (table-> items[index]!= nullptr) { // while there is a collision
        if (table->items[index]->key == key) { // if the key already exists, update the value
            table->items[index]->value = value;
            return;
        }
        index = (index + 1) % table->size; // linear probing to find the next available slot
        
        if(index == start){
            return; // we have looped through the entire table and found no available slot, so we return without inserting
        }
    }
    table->items[index] = ht_new_item(key, value); // insert the new item into the hash table
    table->count++;  
}

std::string _ht_search(const std::unique_ptr<hash_table>& table, const std::string& key){
    int index = ht_hash(key, 31, table->size); 
    int start = index; // to keep track of the starting index for linear probing
    while (table->items[index] != nullptr) { // while there is a collision
        if (table->items[index]->key == key) { // if the key is found, return the value
            return table->items[index]->value;
        }
        index = (index + 1) % table->size; // linear probing to find the next slot
        
        if(index == start){
            break; // we have looped through the entire table and found no available slot, so we break out of the loop
        }
    }
    return ""; // if the key is not found, return an empty string
}

// display formatting 
void print_table(const std::unique_ptr<hash_table>& table) {
    std::cout << "\n--- Hash Table (size=" << table->size << ", count=" << table->count << ") ---\n";
    for (int i = 0; i < table->size; ++i) {
        if (table->items[i] != nullptr) {
            std::cout << "[" << i << "] " << table->items[i]->key
                      << " => " << table->items[i]->value << "\n";
        } else {
            std::cout << "[" << i << "] (empty)\n";
        }
    }
    std::cout << "---------------------------------------------\n";
}

static void _ht_resize_helper(std::unique_ptr<hash_table>& table, int new_size){
    auto new_table = ht_new(new_size);

    for(int i =0; i < table->size; ++i){
        if(table->items[i] != nullptr){
            _ht_insert(new_table, table->items[i]->key, table->items[i]->value); // rehashing the existing items into the new table
        }
    }
    table = std::move(new_table); // replace the old table with the new resized table
}

void _ht_resize_up(std::unique_ptr<hash_table>& table){
    int new_size = next_prime(table->size * 2); // find the next prime number after doubling the current size
    _ht_resize_helper(table, new_size);
    std::cout << "Resized up to " << new_size << "\n";
}

void _ht_resize_down(std::unique_ptr<hash_table>& table){
    int new_size = next_prime(table->size / 2); // find the next prime number after halving the current size
    if (new_size < 5) new_size = 5; // set a minimum size for the hash table to prevent it from becoming too small
    _ht_resize_helper(table, new_size);
    std::cout << "Resized down to " << new_size << "\n";
}

void _ht_delete(std::unique_ptr<hash_table>& table, const std::string& key){
    int index = ht_hash(key, 31, table->size); 
    int start = index; // to keep track of the starting index for linear probing
    while (table->items[index] != nullptr) { // while there is a collision
        if (table->items[index]->key == key) { // if the key is found, delete the item
            table->items[index].reset(); // reset the unique_ptr to delete the item
            table->count--; // decrease the count of items in the hash table
            if(table->count < table->size * 0.2 && table->size > 5){ // if the load factor is less than or equal to 0.25, resize down the hash table
                _ht_resize_down(table);
            }
            return;
        }
        index = (index + 1) % table->size; // linear probing to find the next slot
        
        if(index == start){
            break; // we have looped through the entire table and found no available slot, so we break out of the loop
        }
    }
}