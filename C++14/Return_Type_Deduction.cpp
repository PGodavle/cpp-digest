#include <iostream>

int main() {
    auto multiply = [](int a, int b) { return a * b; };  // Return type deduced as int
    std::cout << "3 * 4 = " << multiply(3, 4) << "\n";
    return 0;
}
