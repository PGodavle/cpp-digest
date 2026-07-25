#include <iostream>

class Multiplier {
private:
    int factor;

public:
    Multiplier(int f) : factor(f) {}

    // Overloading '()' operator
    int operator()(int number) const {
        return number * factor;
    }
};

int main() {
    Multiplier doubleIt(2);
    Multiplier tripleIt(3);

    // Using objects as if they were functions
    std::cout << "Double 5: " << doubleIt(5) << "\n"; // Output: 10
    std::cout << "Triple 5: " << tripleIt(5) << "\n"; // Output: 15
}