#include <iostream>

int main() {
    auto add = [](auto a, auto b) { return a + b; };
    std::cout << "sum of ints: " << add(3, 4) << '\n';           // Output: 7
    std::cout << "sum of doubles: " << add(3.5, 4.2) << '\n';      // Output: 7.7
    return 0;
}
