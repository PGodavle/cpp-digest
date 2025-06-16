#include <iostream>
#include <vector>

class Data {
public:
    std::vector<int> values;

    Data(size_t size) : values(size, 0) {} // Initialize with zeros

    // Copy Constructor (Expensive)
    Data(const Data& other) : values(other.values) {
        std::cout << "Copy Constructor Called\n";
    }

    // Move Constructor (Efficient)
    Data(Data&& other) noexcept : values(std::move(other.values)) {
        std::cout << "Move Constructor Called\n";
    }
};

int main() {
    Data d1(1000000); // Large object
    Data d2 = d1;     // Copy (Expensive)
    Data d3 = std::move(d1); // Move (Efficient)
}
