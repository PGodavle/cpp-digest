#include <iostream>
//Here, the factorial function uses a loop—but when you call it with a compile-time constant, the compiler can evaluate it during compilation.
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;
    return result;
}

int main() {
    constexpr int fact5 = factorial(5);  // Computed at compile time
    std::cout << "Factorial of 5 is " << fact5 << '\n';  // Output: 120
    return 0;
}
