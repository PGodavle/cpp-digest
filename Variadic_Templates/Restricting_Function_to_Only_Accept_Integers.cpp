#include <iostream>
#include <type_traits>
//Ensuring type safety using SFINAE (Substitution Failure Is Not An Error).
template<typename... Args, typename = std::enable_if_t<(std::is_integral_v<Args> && ...)>>
void printIntegers(Args... args) {
    (std::cout << ... << args) << std::endl;
}

int main() {
    printIntegers(1, 2, 3); // Works
    // printIntegers(1, "Hello", 3.14); // Compilation error!
    return 0;
}
