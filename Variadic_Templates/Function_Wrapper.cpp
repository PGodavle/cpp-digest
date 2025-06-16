#include <iostream>
//Variadic templates allow function wrappers that forward arguments dynamically.
template<typename Func, typename... Args>
auto functionWrapper(Func func, Args... args) -> decltype(func(args...)) {
    return func(args...);
}

int add(int a, int b) { return a + b; }

int main() {
    std::cout << functionWrapper(add, 5, 3) << std::endl; // Output: 8
    return 0;
}
