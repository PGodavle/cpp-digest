#include <iostream>
#include <memory>

struct Data {
    int value;
};

int main() {
    auto ptr = std::make_unique<Data>();  // No need to use new directly
    ptr->value = 42;
    std::cout << "Data value: " << ptr->value << "\n";
    return 0;
}
