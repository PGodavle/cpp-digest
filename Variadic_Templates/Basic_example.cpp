#include <iostream>

// Args... represents a parameter pack.
// (std::cout << ... << args) expands the pack using a fold expression (C++17).
// The function can accept any number of arguments.

template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << std::endl; // Fold expression (C++17)
}

int main() {
    print(1, 2, 3, "Hello", 4.5); // Prints: 123Hello4.5
    return 0;
}
