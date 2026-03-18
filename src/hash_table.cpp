#include<string>
#include<memory>
#include "hash_table.h"


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