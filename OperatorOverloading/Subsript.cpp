#include <iostream>
#include <stdexcept>

class SafeArray {
private:
    int arr[5] = {10, 20, 30, 40, 50};

public:
    // Non-const version (allows modification: arr[0] = 99)
    int& operator[](int index) {
        if (index < 0 || index >= 5) {
            throw std::out_of_range("Index out of bounds!");
        }
        return arr[index];
    }

    // Const version (read-only access for const objects)
    const int& operator[](int index) const {
        if (index < 0 || index >= 5) {
            throw std::out_of_range("Index out of bounds!");
        }
        return arr[index];
    }
};

int main() {
    SafeArray list;
    list[2] = 100; // Modifies 3rd element
    std::cout << "Element at 2: " << list[2] << "\n";
}