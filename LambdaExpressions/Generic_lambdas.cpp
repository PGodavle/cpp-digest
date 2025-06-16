#include <iostream>
//C++ 14
int main() {
    auto add = [](auto a, auto b) {
        return a + b;
    };

    std::cout << add(3, 4) << "\n";       // Works with ints
    std::cout << add(3.5, 2.5) << "\n";     // Works with doubles
    return 0;
}
