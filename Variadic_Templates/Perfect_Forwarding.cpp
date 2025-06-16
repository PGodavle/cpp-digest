#include <iostream>

template<typename... Args>
void forwardArgs(Args&&... args) {
    (std::cout << ... << args) << std::endl;
}

int main() {
    forwardArgs(1, "Hello", 3.14); // Preserves types
    return 0;
}
