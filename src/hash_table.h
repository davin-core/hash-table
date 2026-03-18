#pragma once
#include <string>
#include <vector>
#include <memory>
// key-value pair item

struct ht_item {
    std::string key;
    std::string value;
};

// hash table store an array of pointers, size and whether it is full or not
struct hash_table {
    std::vector<std::unique_ptr<ht_item>> items;
    int size = 0;
    int count = 0;
}; 

// Factory functions
std::unique_ptr<ht_item> ht_new_item(const std::string& key, const std::string& value);
std::unique_ptr<hash_table> ht_new(int size);
// we don't need this because we use unique_ptr to manage memory, it will automatically delete the hash_table when it goes out of scope
//void ht_del_hash_table(std::unique_ptr<hash_table>& table);


