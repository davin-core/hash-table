#include "hash_table.h"
#include <iostream>
int main(){
    auto table = ht_new(10);

    while (true) {
        std::cout << "\nChoose an action:\n"
                  << "1) Insert key/value\n"
                  << "2) Search key\n"
                  << "3) Print table\n"
                  << "4) Exit\n"
                  << "> ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string key, value;
            std::cout << "Key: ";
            std::getline(std::cin, key);
            std::cout << "Value: ";
            std::getline(std::cin, value);

            _ht_insert(table, key, value);
            std::cout << "Insert attempted.\n";
        }
        else if (choice == "2") {
            std::string key;
            std::cout << "Key to search: ";
            std::getline(std::cin, key);

            std::string value = _ht_search(table, key);
            if (value.empty()) {
                std::cout << "Not found.\n";
            } else {
                std::cout << "Found: " << key << " => " << value << "\n";
            }
        }
        else if (choice == "3") {
            print_table(table);
        }
        else if (choice == "4") {
            break;
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}