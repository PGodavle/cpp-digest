#include <iostream>
#include <utility>

template<typename T, T... Ints>
void printSequence(std::integer_sequence<T, Ints...>) {
    // Using an initializer list trick to expand the pack
    int dummy[] = { (std::cout << Ints << ' ', 0)... };
    (void)dummy;
}

int main() {
    std::cout << "Integer sequence: ";
    printSequence(std::integer_sequence<int, 1, 2, 3, 4, 5>{});
    std::cout << "\n";
    return 0;
}
