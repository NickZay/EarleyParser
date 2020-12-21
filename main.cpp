#include <iostream>
#include "Earley.h"

int main() {
    Grammar grammar;
    std::string string;

    try {
        std::cin >> grammar >> string;
        if (Early(grammar).Check(string)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    } catch (std::exception& ex) {
        std::cout << ex.what();
    }

    return 0;
}