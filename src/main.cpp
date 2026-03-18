#include "hash_table.h"
#include <iostream>
int main(){
    auto table = ht_new(10);
    table->items[0] = ht_new_item("key1", "value1");
    table->items[1] = ht_new_item("key2", "value2");

    std::cout << "Hash Table Size: " << table->size << std::endl;
    std::cout << "Item 0: " << table->items[0]->key << " => " << table->items[0]->value << std::endl;
    std::cout << "Item 1: " << table->items[1]->key << " => " << table->items[1]->value << std::endl;

    std::cout << "Press Enter to exit...";
    std::cin.get(); // Wait for user input before closing
    return 0;
}