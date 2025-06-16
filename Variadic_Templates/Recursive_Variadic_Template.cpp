#include <iostream>

// The function processes one argument at a time.
// Calls itself recursively until no arguments remain.

void print() { std::cout << "End of recursion.\n"; }

template<typename First, typename... Rest>
void print(First first, Rest... rest) {
    std::cout << first << " ";
    print(rest...); // Recursive call
}

int main() {
    print(1, "Hello", 3.14, 'A'); // Prints: 1 Hello 3.14 A End of recursion.
    return 0;
}
