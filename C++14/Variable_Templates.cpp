#include <iostream>
//here, pi can be used with any numeric type. This allows for precise control over the type of floating-point constant you need.
template<typename T>
constexpr T pi = T(3.1415926535897932385L);

int main() {
    std::cout << "pi<float>: " << pi<float> << "\n";
    std::cout << "pi<double>: " << pi<double> << "\n";
    return 0;
}
