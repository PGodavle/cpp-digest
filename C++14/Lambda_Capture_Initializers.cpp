#include <iostream>
#include <vector>
#include <memory>
//The capture [myPtr = std::move(ptr)] moves ptr into the lambda, creating a local name myPtr. This pattern is very useful when working with move-only types or when you want to initialize a captured variable with an expression.
int main() {
    std::unique_ptr<int> ptr(new int(10));
    // Capture ptr by moving it into the lambda, renaming it to myPtr.
    auto lambda = [myPtr = std::move(ptr)]() {
        std::cout << "Value: " << *myPtr << '\n';
    };
    lambda();

    // ptr is now empty after the move.
    if (!ptr)
        std::cout << "ptr is nullptr after move.\n";
    return 0;
}
