#include <iostream>
//C++ std::tuple is implemented using variadic templates.

template<typename... Types>
class MyTuple {};

int main() {
    MyTuple<int, double, std::string> myTuple; // Works with multiple types
    return 0;
}
