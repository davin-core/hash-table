#include "hash_table.h"
#include <iostream>
int main(){
    auto table = ht_new(10);
    while (true) {
        std::cout << "\nChoose an action:\n"
                << "1) Insert/Update key-value\n"
                << "2) Search key\n"
                << "3) Delete key\n"
                << "4) Print table\n"
                << "5) Resize UP (manual)\n"
                << "6) Resize DOWN (manual)\n"
                << "7) Exit\n"
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
            std::cout << "Insert/Update attempted.\n";
        }
        else if (choice == "2") {
            std::string key;
            std::cout << "Key to search: ";
            std::getline(std::cin, key);

            std::string value = _ht_search(table, key);
            if (value.empty()) {
                std::cout << "Not found (or value is empty string).\n";
            } else {
                std::cout << "Found: " << key << " => " << value << "\n";
            }
        }
        else if (choice == "3") {
            std::string key;
            std::cout << "Key to delete: ";
            std::getline(std::cin, key);

            _ht_delete(table, key);
            std::cout << "Delete attempted.\n";
        }
        else if (choice == "4") {
            print_table(table);
        }
        else if (choice == "5") {
            _ht_resize_up(table);
        }
        else if (choice == "6") {
            _ht_resize_down(table);
        }
        else if (choice == "7") {
            break;
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}